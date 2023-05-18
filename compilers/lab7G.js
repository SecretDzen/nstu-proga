var ignoreLastWord;

var idReg = /^[_][a-zA-Z0-9]+[_]$/
var binaryReg = /([+\-*^><=])|([&][&])|([|][|])|([!=><][=])/
var unaryReg = /^[m!]$/
var actionReg = /^[A-Z]+$/
var markReg = /[A-Z]+[#][0-9]/
var goMarkReg = /[A-Z]+[#][0-9][:]/

var numReg = /[0-9]([.][0-9])*/
var stringReg = /["][a-zA-Z]+["]/

var ASM = class ASM {
  constructor(rpn) {
    this.rpn_ = rpn.split(' ')
    this.asm_ = [] // {label: '', code: '', op1: '', op2: ''}
    this.queue_ = []
    this.label_ = null

    this.counter_ = 1
  }

  getAll() {
    this.form()
    const title = '\n\nПсевдокод\n'
    const body = this.asmToVtb()

    return title + body
  }

  asmToVtb() {
    let body = ''
    this.asm_.forEach((e) => {
      body += `${e.code} ${e.op1} ${e.op2} ${e.res}\n`
    })
    return body
  }

  form() {
    while (this.rpn_.length) {
      const item = this.rpn_.shift()
      if (item.match(actionReg)) {
        this.handleAction(item)
      } else if (item.match(binaryReg)) {
        this.handleBinary(item)
      } else if (item.match(unaryReg)) {
        this.handleUnary(item)
      } else if (item.match(goMarkReg)) {
        this.handleGoMark(item)
      } else {
        this.queue_.push(item)
      }
    }
  }

  handleGoMark(goMark) {
    this.asm_.push({ code: 'defineLabel', op1: goMark, op2: null, res: null })
  }

  handleBinary(code) {
    const [op1, op2] = this.useBinaryAction()
    let count = code === '='
      ? this.useLastDeclare()
      : `tempVar${this.counter_++}`

    const item = { code, op1, op2, res: count }
    this.asm_.push(item)
  }

  handleUnary(code) {
    const op1 = this.useUnaryAction()
    const item = { code, op1, op2: null, res: `tempVar${this.counter_++}` }
    this.asm_.push(item)
  }

  handleAction(act) {
    if (act === 'FUNC' || act === 'VAR') {
      const [op1, op2] = this.useBinaryAction()
      const item = { code: act, op1, op2, res: op1 }
      this.asm_.push(item)
    } else if (act === 'JMPF') {
      const [op1, op2] = this.useBinaryAction()
      const item = { code: act, op1, op2, res: null }
      this.asm_.push(item)
    } else if (act === 'CALL') {
      const op1 = this.useUnaryAction()
      const item = { code: act, op1, op2: `tempVar${this.counter_++}`, res: null }
      this.asm_.push(item)
    } else {
      const op1 = this.useUnaryAction()
      const item = { code: act, op1, op2: null, res: null }
      this.asm_.push(item)
    }
  }

  useUnaryAction() {
    const op = this.queue_.shift() || this.useLastDeclare()
    return op
  }

  useBinaryAction() {
    const op1 = this.queue_.shift() || this.useLastDeclare()
    const op2 = this.queue_.shift() || this.useLastDeclare()

    return [op1, op2]
  }

  useLastDeclare() {
    if (this.counter_ > 1) {
      return `tempVar${--this.counter_}`
    }

    let i = this.asm_.length

    while (i-- !== 1) {
      if (this.asm_[i].code === 'VAR') {
        return this.asm_[i].op1
      }
    }
  }

  peekAsm() {
    return this.asm_[this.asm_.length - 1]
  }
}

var RPN = class RPN {
  constructor() {
    this.rpn_ = []
    this.stack_ = []
    this.temp_ = []
    this.depth_ = 0

    this.funcCounter_ = 0

    this.loopDepth_ = 0
    this.loopFrom_ = 0
    this.loopTo_ = 0
    this.loopVar_ = ''
  }

  clear() {
    this.rpn_ = []
    this.stack_ = []
    this.temp_ = []
    this.depth_ = 0

    this.funcCounter_ = 0

    this.loopDepth_ = 0
    this.loopFrom_ = 0
    this.loopTo_ = 0
    this.loopVar_ = ''
  }

  getAll() {
    const title = 'Постфикс:\n'
    const body = this.rpn_.join(' ')
    const asm = new ASM(body)

    return title + body + asm.getAll()
  }

  operator(vtb, isUnary = false) {
    let op = vtb.currentLexem[1]
    if (isUnary) {
      op = op === '-' ? 'm' : op
      op = op === '+' ? 'p' : op
    }

    const pr = this.getPrior(op)

    if (this.stack_.length === 0) {
      this.stack_.push(op)
    } else {
      const stackOp = this.peekStack()
      const stackPr = this.getPrior(stackOp)

      if (pr > stackPr) {
        this.stack_.push(op)
      } else {
        this.popStack(pr)
        this.stack_.push(op)
      }
    }
  }

  operand(vtb) {
    const op = vtb.currentLexem[1]
    this.rpn_.push(op)
  }

  peekStack() {
    return this.stack_[this.stack_.length - 1]
  }

  pushStack(vtb) {
    const op = vtb.currentLexem[1]
    this.stack_.push(op)
  }

  popStack(pr) {
    while (this.stack_.length) {
      const stackOp = this.peekStack()
      const stackPr = this.getPrior(stackOp)

      if (stackPr === 50) break
      if (pr > stackPr) break

      this.rpn_.push(this.stack_.pop())
    }
  }

  openScope() {
    this.stack_.push('(')
  }

  closeScope() {
    this.popStack(0)
    this.stack_.pop()
  }

  action(name) {
    if (name === 'arg') {
      this.popStack(0)
      this.rpn_.push('ARG')
    }

    if (name === 'carg') {
      this.popStack(0)
      this.rpn_.push('CARG')
    }

    if (name === 'call') {
      this.popStack(0)
      this.rpn_.push('CALL')
    }

    if (name === 'ret') {
      this.popStack(0)
      this.rpn_.push('RET')
      this.rpn_.push('ENDFN#' + this.funcCounter_)
      this.rpn_.push('JMP')
    }

    if (name === 'var') {
      let temp = []

      while (true) {
        let lex = this.rpn_[this.rpn_.length - 1]
        if (lex.includes('#') || lex.match(actionReg) || lex === '=') {
          break
        }
        temp.push(this.rpn_.pop())
      }

      const variable = this.stack_.pop()
      const type = this.stack_.pop()

      this.rpn_.push(variable)
      this.rpn_.push(type)
      this.rpn_.push('VAR')

      while (temp.length) this.rpn_.push(temp.pop())

      this.popStack(0)
      this.rpn_.push('=')
    }

    if (name === 'func') {
      this.popStack(0)
      this.rpn_.push('FUNC')
    }

    if (name === 'funcL') {
      this.rpn_.push(`FN#${this.funcCounter_}:`)
    }

    if (name === 'fnEnd') {
      this.rpn_.push(`ENDFN#${this.funcCounter_}:`)
      this.funcCounter_++
    }

    if (name === 'at') {
      this.depth_++
      this.popStack(0)
      this.rpn_.push('ELSE#' + this.depth_)
      this.rpn_.push('JMPF')
    }

    if (name === 'else') {
      this.popStack(0)
      this.rpn_.push('END#' + this.depth_)
      this.rpn_.push('JMP')
      this.rpn_.push(`ELSE#${this.depth_}:`)
    }

    if (name === 'end') {
      this.popStack(0)
      this.rpn_.push(`END#${this.depth_}:`)
      this.depth_--
    }

    if (name === 'loopEnd') {
      this.rpn_.push(this.loopVar_)
      while (this.temp_.length) this.rpn_.push(this.temp_.pop())
      this.rpn_.push('=')
      this.rpn_.push(`LOOP#${this.loopDepth_}`)
      this.rpn_.push(`JMP`)
      this.rpn_.push(`END#${this.loopDepth_}:`)

      this.depth_--
    }

    if (name === 'loopTo') {
      this.depth_++
      this.loopDepth_ = this.depth_

      this.popStack(0)
      let temp = []

      while (true) {
        let lex = this.rpn_[this.rpn_.length - 1]
        if (lex === 'VAR') break
        temp.push(this.rpn_.pop())
      }

      this.loopVar_ = this.rpn_[this.rpn_.length - 3]

      while (temp.length) {
        let lex = temp.pop()
        this.rpn_.push(lex)
        if (lex === '=') break
      }

      this.rpn_.push(`LOOP#${this.loopDepth_}:`)
      while (temp.length) this.rpn_.push(temp.pop())

      this.rpn_.push(`END#${this.loopDepth_}`)
      this.rpn_.push(`JMPF`)
    }

    if (name === 'loopStep') {
      this.popStack(0)

      while (true) {
        let lex = this.rpn_[this.rpn_.length - 1]
        if (lex === 'JMPF') break
        this.temp_.push(this.rpn_.pop())
      }
    }

    if (name === 'break') {
      this.rpn_.push(`END#${this.loopDepth_}`)
      this.rpn_.push(`JMP`)
    }
  }

  getPrior(lex) {
    switch (lex) {
      case '<':
      case '>':
      case '>=':
      case '<=':
      case '!=':
        return 5

      case "+":
      case "-":
        return 10

      case "*":
      case "/":
        return 20

      case "^":
        return 30

      case "m":
      case "!":
      case "p":
        return 40

      case '(':
        return 50
    }
    return 0
  }
}

var tracer = new RPN()