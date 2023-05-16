var ignoreLastWord;

var idReg = /[a-z][0-9]{1,4}[a-z]/
var binaryReg = /([+\-*^><=])|([&][&])|([|][|])|([!=><][=])/
var unaryReg = /[mp!]/
var actionReg = /[<][A-Z_#0-9]+[>]/

var RPN = class RPN {
  constructor() {
    this.rpn_ = []
    this.stack_ = []
    this.depth_ = 0

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

    if (this.stack_.length) {
      console.log("STACK NOT EMPTY")
      console.log(this.stack_)
    }

    return title + body
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