var ignoreLastWord;

var idReg = /[a-z][0-9]{1,4}[a-z]/
var binaryReg = /([+\-*^><=])|([&][&])|([|][|])|([!=><][=])/
var unaryReg = /[mp!]/
var actionReg = /[<][A-Z]+[>]/
var markReg = /[A_Z][#][0-9]/
var goMarkReg = /[A_Z][#][0-9][:]/

var numReg = /[0-9]([.][0-9])*/
var stringReg = /["][a-zA-Z]+["]/

var VM = class VM {
  constructor(asm) {
    this.asm_ = asm // {label: '', code: '', op1: '', op2: ''}
    this.vm_ = [] // {func: 'name', type: 'int', args: [{name: 'a1a', type: 'int', value: 0}], vars: [as args], value: null}
    this.tempVar_ = 0
    this.out_ = []
    this.isError_ = false
    this.textError_ = ''
  }

  getAll() {
    this.form()
    const title = '\n\n=== VM ===\n'
    const body = this.out_.join('\n')
    return title + body
  }

  form() {
    console.log('start')

    for (let i = 0; i < this.asm_.length && !this.isError_; i++) {
      console.log("on line: ")
      console.log(this.asm_[i])
      if (this.asm_[i].code.match(actionReg)) {
        this.handleAction(this.asm_[i])
      } else if (this.asm_[i].code.match(binaryReg)) {
        this.handleBinary(this.asm_[i])
      }
      console.log("success line")

    }

    console.log('end')
    if (this.isError_) this.throwError()
  }

  handleBinary(line) {
    if (line.code === '=') {
      const func = this.peek(this.vm_)
      const lastVar = this.peek(func.vars)

      if (line.op1 === 'STACK') {
        this.setValue(lastVar, this.tempVar_)
        this.tempVar_ = 0
      } else {
        this.setValue(lastVar, line.op1)
      }

      if (!this.isError_) {
        this.out_.push(`= ${lastVar.value} ${lastVar.name}`)
      }
    }

    if (line.code === '+') {
      let [num1, num2] = this.useBinaryAction(line.op1, line.op2)

      if (!num2) {
        num2 = this.tempVar_
      }

      this.tempVar_ = num1 + num2
      if (!this.isError_) {
        this.out_.push(`+ ${num1} ${num2}`)
      }
    }
  }

  handleAction(line) {
    if (line.code === '<FUNC>') {
      const func = {
        name: line.op1,
        type: line.op2,
        args: [],
        vars: [],
        value: null
      }

      this.vm_.push(func)
    }

    if (line.code === '<VAR>') {
      const initVal = this.initValue(line.op2)
      const variable = { name: line.op1, type: line.op2, value: initVal }

      const func = this.peek(this.vm_)
      func.vars.push(variable)
    }

    if (line.code === '<RET>') {
      const func = this.peek(this.vm_)

      if (line.op1 === 'STACK') {
        console.log('RETURN STACK')
      } else if (line.op1.match(idReg)) {
        const variable = this.findVar(func, line.op1)
        if (variable) this.setValue(func, variable.value)
      } else {
        this.setValue(func, line.op1)
      }

      if (!this.isError_) {
        this.out_.push(`RET ${func.value} ${func.name}`)
      }
    }
  }

  setValue(obj, value) {
    if (!this.typeCheck(obj, value)) {
      this.isError_ = true
      this.textError_ = `ERR ${obj.name} type is ${obj.type}. Value passed: ${value}`
    }
    obj.value = value
  }

  findVar(func, varName) {
    const variable = func.vars.find((e) => e.name === varName)

    if (!variable) {
      this.isError_ = true
      this.textError_ = `ERR no such variable ${varName}`
    }

    return variable
  }

  useUnaryAction() {

  }

  useBinaryAction(op1, op2) {
    return [Number.parseInt(op1), Number.parseInt(op2)]
  }

  typeCheck(obj, value) {
    if (`${value}`.match(numReg)) {
      return obj.type === 'int'
    } else if (value.match(stringReg)) {
      return obj.type === 'string'
    } else {
      return obj.type === 'char'
    }
  }

  peek(arr) {
    return arr[arr.length - 1]
  }

  initValue(type) {
    return type === 'int' ? 0 : ''
  }

  throwError() {
    this.out_.push(this.textError_)
    this.out_.push(`ERR Aborting...`)
  }
}

var ASM = class ASM {
  constructor(rpn) {
    this.rpn_ = rpn.split(' ')
    this.asm_ = [] // {label: '', code: '', op1: '', op2: ''}
    this.queue_ = []
  }

  getAll() {
    this.form()
    const vm = new VM(this.asm_)
    const title = '\n\n=== ASM ===\n'
    const body = this.asmToVtb()

    return title + body
  }

  asmToVtb() {
    let body = ''
    this.asm_.forEach((e) => {
      body += `${e.label} ${e.code} ${e.op1} ${e.op2}\n`
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
      } else {
        this.queue_.push(item)
      }
    }
  }

  handleBinary(code) {
    const [op1, op2] = this.useBinaryAction()
    const item = { label: 'null', code, op1, op2 }
    this.asm_.push(item)
  }

  handleAction(act) {
    if (act === '<FUNC>') {
      const [op1, op2] = this.useBinaryAction()
      const item = { label: 'null', code: act, op1, op2 }
      this.asm_.push(item)
    }

    if (act === '<CALL>') {
      const op1 = this.useUnaryAction()
      const item = { label: 'null', code: act, op1, op2: 'null' }
      this.asm_.push(item)
    }

    if (act === '<CARG>') {
      const op1 = this.useUnaryAction()
      const item = { label: 'null', code: act, op1, op2: 'null' }
      this.asm_.push(item)
    }

    if (act === '<VAR>') {
      const [op1, op2] = this.useBinaryAction()
      const item = { label: 'null', code: act, op1, op2 }
      this.asm_.push(item)
    }

    if (act === '<JMPF>') {

    }

    if (act === '<JMP>') {

    }

    if (act === '<RET>') {
      const op1 = this.useUnaryAction()
      const item = { label: 'null', code: act, op1, op2: 'null' }
      this.asm_.push(item)
    }
  }

  useUnaryAction() {
    const op = this.queue_.shift() || 'STACK'
    return op
  }

  useBinaryAction() {
    const op1 = this.queue_.shift() || 'STACK'
    const op2 = this.queue_.shift() || 'STACK'

    return [op1, op2]
  }
}

var RPN = class RPN {
  constructor() {
    this.rpn_ = []
    this.stack_ = []
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
    this.depth_ = 0

    this.loopDepth_ = 0
    this.loopFrom_ = 0
    this.loopTo_ = 0
    this.loopVar_ = ''
  }

  getAll() {
    const title = '=== RPN ===\n'
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
      this.rpn_.push('<ARG>')
    }

    if (name === 'carg') {
      this.popStack(0)
      this.rpn_.push('<CARG>')
    }

    if (name === 'call') {
      this.popStack(0)
      this.rpn_.push('<CALL>')
    }

    if (name === 'ret') {
      this.popStack(0)
      this.rpn_.push('<RET>')
    }

    if (name === 'var') {
      this.popStack(0)
      this.rpn_.push('<VAR>')
    }

    if (name === 'func') {
      this.popStack(0)
      this.rpn_.push('<FUNC>')
    }

    if (name === '=') {
      this.popStack(0)
      this.rpn_.push('=')
    }

    if (name === 'by') {
      this.depth_++
      this.popStack(0)
      this.rpn_.push('ELSE#' + this.depth_)
      this.rpn_.push('<JMPF>')
    }

    if (name === 'else') {
      this.popStack(0)
      this.rpn_.push('END#' + this.depth_)
      this.rpn_.push('<JMP>')
      this.rpn_.push(`ELSE#${this.depth_}:`)
    }

    if (name === 'end') {
      this.popStack(0)
      this.rpn_.push(`END#${this.depth_}:`)
      this.depth_--
    }

    if (name === 'loop') {
      this.depth_++
      this.loopDepth_ = this.depth_

      this.loopTo_ = this.stack_.pop()
      this.loopFrom_ = this.stack_.pop()

      this.action('var')
      this.loopVar_ = this.rpn_[this.rpn_.length - 3]

      this.rpn_.push(this.loopFrom_)
      this.rpn_.push('=')

      this.rpn_.push(`LOOP#${this.loopDepth_}:`)

      this.rpn_.push(this.loopVar_)
      this.rpn_.push(this.loopTo_)
      this.rpn_.push('<')

      this.rpn_.push(`END#${this.loopDepth_}`)
      this.rpn_.push(`<JMPF>`)
    }

    if (name === 'endLoop') {
      this.rpn_.push(this.loopVar_)
      this.rpn_.push('1')
      this.rpn_.push('+')
      this.rpn_.push('=')

      this.rpn_.push(`LOOP#${this.loopDepth_}`)
      this.rpn_.push(`<JMP>`)
      this.rpn_.push(`END#${this.loopDepth_}:`)

      this.depth_--
    }

    if (name === 'break') {
      this.rpn_.push(`END#${this.loopDepth_}`)
      this.rpn_.push(`<JMP>`)
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