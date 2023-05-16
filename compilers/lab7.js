var ignoreLastWord;

var TYPES = {
  OPERAND: 0,
  OPERATOR: 1,
  OPEN_BRACKET: 2,
  CLOSE_BRACKET: 3,
  VAR_TYPE: 4,
  FUNCTION: 5,
  FN_ARGS: 6,
  ASSIGN: 7,
  CONDITION: 8,
  LOOP: 9,
  JMP_E: 10,
  JMP: 11,
  JMP_L: 12,
}

var binaryPattern = /[+\-*\/^<>]/
var unaryPattern = /[!mp]/

var Pseudo = class Pseudo {
  constructor(postfix) {
    this.postfix_ = postfix.split(' ')
    this.stack_ = []
    this.temp_ = []
    this.vars_ = []
    this.pseudocode_ = [] // { label: 'FUNC#0', code: 'DEC_FN', fromOp: 'd1d', toOp: 'int' }
  }

  getText() {
    this.postfix_.shift()

    const title = '\n\n=== Псевдокод ===\n'
    const subtitle = '| Метка | Код | Операнд | Операнд |\n'
    this.handlePostfix()
    const body = this.getPseudoCode()

    return title + subtitle + body
  }

  getPseudoCode() {
    let body = ''
    this.pseudocode_.forEach((e) => {
      body += `| ${e.label} | ${e.code} | ${e.fromOp} | ${e.toOp} |\n`
    })

    return body
  }

  peekCode(num = 1) {
    return this.pseudocode_[this.pseudocode_.length - num]
  }

  handlePostfix() {
    this.postfix_.forEach((el) => {
      if (el.includes('#')) {
        this.handleElement(el)
      } else if (el.includes('JMP')) {
        this.handleJump(el)
      } else {
        this.stack_.push(el)
      }
    })
  }

  handleJump(el) {
    let labelNum = this.peekCode().label.split('#')[1]
    for (let i = 1; i < this.pseudocode_.length && labelNum === undefined; i++) {
      labelNum = this.peekCode(i).label.split('#')[1]
    }

    if (el === 'JMP_E') {
      this.pushPseudo('-----', el, 'tempVar#' + labelNum, this.peekCode().label)
    }

    if (el === 'JMP') {
      this.pushPseudo('-----', el, 'tempVar#' + labelNum, 'END_COND#' + labelNum)
    }

    if (el === 'JMP_F') {
      this.pushPseudo('-----', el, '-----', 'STACK')
    }
  }

  handleElement(el) {
    const [label, idx] = el.split('#')

    if (label === 'FUNC') {
      let type = this.stack_.pop()
      let name = this.stack_.pop()
      this.pushPseudo(el, 'DEC_FN', name, type)
      this.vars_.push(name)
    }

    if (label === 'RETURN') {
      this.exprHandler(el)

      const fn = this.pseudocode_.find((e) => e.label === `FUNC#${idx}`)

      if (this.temp_.length) {
        this.pushPseudo(el, 'MOVE', this.temp_.pop(), fn.fromOp)
      } else {
        this.pushPseudo(el, 'MOVE', 'STACK', fn.fromOp)
      }
    }

    if (label === 'ASSIGN') this.declareVar(el)

    if (label === 'FN_ARGS') {
      while (this.stack_.length) {
        this.declareVar(el)
      }
    }

    if (label === 'CALL_ARGS') {
      this.exprHandler(el)

      if (this.temp_.length !== 1) {
        this.pushPseudo(el, 'MOVE', this.temp_.pop(), `var${idx}`)
      } else {
        this.pushPseudo(el, 'MOVE', 'STACK', `var${idx}`)
      }
      
    }

    if (label === 'END_ASSIGN') {
      this.exprHandler(el)

      if (this.temp_.length) {
        this.pushPseudo(el, 'MOVE', this.temp_.pop(), this.vars_.pop())
      } else {
        this.pushPseudo(el, 'MOVE', 'STACK', this.vars_.pop())
      }
    }

    if (label === 'COND') {
      this.exprHandler(el)

      if (this.temp_.length) {
        this.pushPseudo(el, 'MOVE', this.temp_.pop(), this.vars_.pop())
      } else {
        this.pushPseudo(el, 'MOVE', 'STACK', 'tempVar#' + this.peekCode().label.split('#')[1])
      }
    }

    if (label === 'ELSE_COND' || label === 'END_COND' || label === 'END_LOOP') {
      this.pushPseudo(el, '-----', '-----', '-----')
    }

    if (label === 'EXIT') {
      this.pushPseudo(el, 'JMP', 'END_COND#' + idx, '-----')

    }
  }

  exprHandler(el) {
    while (this.stack_.length) {
      let lex = this.stack_.shift()

      if (lex.match(binaryPattern)) {
        const left = (this.temp_.length) ? this.temp_.pop() : 'STACK'
        const right = (this.temp_.length) ? this.temp_.pop() : 'STACK'
        this.pushPseudo(el, lex, left, right)
      } else if (lex.match(unaryPattern)) {
        const left = (this.temp_.length) ? this.temp_.pop() : 'STACK'
        this.pushPseudo(el, lex, left, 'STACK')
      } else {
        this.temp_.push(lex);
      }
    }
  }

  declareVar(el) {
    let type = this.stack_.pop()
    let name = this.stack_.pop()
    this.pushPseudo(el, 'DEC_VAR', name, type)
    this.vars_.push(name)
  }

  pushPseudo(label, code, fromOp, toOp) {
    this.pseudocode_.push({ label, code, fromOp, toOp })
  }
}

var Tracer = class Tracer {
  constructor() {
    this.postfix_ = []
    this.operators_ = [] // {lex: "+", type: TYPES.OPERAND, priority: 10}
    this.variableType_ = ''

    this.depth_ = 0
    this.func_ = 0

    this.loopFrom_ = 0
    this.loopTo_ = 0
    this.loopVar_ = ''
    this.loopDepth_ = 0
    this.callFn_ = 0
  }

  getAll() {
    const lexems = this.postfix_.reduce((prev, cur) => prev += ' ' + cur.lex, '')
    const postfix = '=== Постфикс ===\n' + lexems
    const pseudocode = new Pseudo(lexems)

    return postfix + pseudocode.getText()
  }

  clear() {
    this.postfix_ = []
    this.operators_ = []
    this.variableType_ = ''

    this.depth_ = 0
    this.func_ = 0

    this.loopFrom_ = 0
    this.loopTo_ = 0
    this.loopDepth_ = 0
    this.callFn_ = 0
    this.loopVar_ = ''
  }

  handleVtb(vtb, type, handler = getPrior, unary) {
    let lex = vtb.currentLexem[1]
    if (unary) lex = lex === '-' ? 'm' : 'p'

    const lexem = { lex, type, priority: handler(lex) }
    return lexem
  }

  operator(vtb) {
    const lexem = this.handleVtb(vtb, TYPES.OPERATOR)

    if (this.operators_.length < 1) {
      this.operators_.push(lexem)
    } else {
      this.handleOperator(lexem)
    }
  }

  unOperator(vtb) {
    const lexem = this.handleVtb(vtb, TYPES.OPERATOR, getPrior, true)

    if (this.operators_.length < 1) {
      this.operators_.push(lexem)
    } else {
      this.handleOperator(lexem)
    }
  }

  operand(vtb) {
    const lexem = this.handleVtb(vtb, TYPES.OPERAND, () => 0)
    this.postfix_.push(lexem)

    if (lexem.lex.match(/[a-z][0-9]{1,4}[a-z]/)) {
      if (this.variableType_ !== '') {
        this.postfix_.push(this.variableType_)
        this.variableType_ = ''
      }
    }
  }

  endOfExpr() {
    while (this.operators_.length) {
      const lexem = this.operators_.pop()
      if (lexem.lex !== "(") this.postfix_.push(lexem)
    }
  }

  type(vtb) {
    const lexem = this.handleVtb(vtb, TYPES.VAR_TYPE, () => 0)
    this.variableType_ = lexem
  }

  func() {
    const lexem = { lex: `FUNC#${this.func_}`, type: TYPES.FUNCTION, priority: 0 }
    this.postfix_.push(lexem)
  }

  endFunc() {
    const lexem = { lex: `RETURN#${this.func_}`, type: TYPES.FUNCTION, priority: 0 }
    this.postfix_.push(lexem)
  }

  callFunc() {
    const lexem = { lex: `JMP_F`, type: TYPES.FUNCTION, priority: 0 }
    this.postfix_.push(lexem)
  }

  callArgs() {
    const lexem = { lex: `CALL_ARGS#${this.callFn_}`, type: TYPES.FN_ARGS, priority: 0 }
    this.postfix_.push(lexem)
    this.callFn_++
  }

  fnArgs() {
    const lexem = { lex: `FN_ARGS#${this.func_}`, type: TYPES.FN_ARGS, priority: 0 }
    this.postfix_.push(lexem)
  }

  assign() {
    const lexem = { lex: `ASSIGN#${this.depth_}`, type: TYPES.ASSIGN, priority: 0 }
    this.postfix_.push(lexem)
  }

  endAssign() {
    const lexem = { lex: `END_ASSIGN#${this.depth_}`, type: TYPES.ASSIGN, priority: 0 }
    this.postfix_.push(lexem)
  }

  condLabel() {
    this.depth_++

    const lexem = { lex: `COND#${this.depth_}`, type: TYPES.CONDITION, priority: 0 }
    this.postfix_.push(lexem)

    const jmp = { lex: `JMP_E`, type: TYPES.JMP_E, priority: 0 }
    this.postfix_.push(jmp)
  }

  condElse() {
    const lexem = { lex: `ELSE_COND#${this.depth_}`, type: TYPES.CONDITION, priority: 0 }
    this.postfix_.push(lexem)

    const jmp = { lex: `JMP`, type: TYPES.JMP, priority: 0 }
    this.postfix_.push(jmp)
  }

  condEnd() {
    const lexem = { lex: `END_COND#${this.depth_}`, type: TYPES.CONDITION, priority: 0 }
    this.postfix_.push(lexem)
    this.depth_--
  }

  loop() {
    this.loopVar_ = this.postfix_[this.postfix_.length - 2]

    this.depth_++
    this.loopDepth_ = this.depth_
    this.assign()
    this.postfix_.push(this.loopFrom_)
    this.endAssign()

    this.postfix_.push(this.loopVar_)
    this.postfix_.push(this.loopTo_)
    this.postfix_.push({ lex: "<", type: TYPES.OPERATOR, priority: 0 })

    const lexem = { lex: `COND#${this.depth_}`, type: TYPES.LOOP, priority: 0 }
    this.postfix_.push(lexem)

    const jmp = { lex: `JMP`, type: TYPES.JMP, priority: 0 }
    this.postfix_.push(jmp)
  }

  loopFrom(vtb) {
    const lexem = this.handleVtb(vtb, TYPES.OPERAND, () => 0)
    this.loopFrom_ = lexem
  }

  loopTo(vtb) {
    const lexem = this.handleVtb(vtb, TYPES.OPERAND, () => 0)
    this.loopTo_ = lexem
  }

  endLoop(isBreak = false) {
    if (!isBreak) {

      this.postfix_.push(this.loopVar_)
      this.postfix_.push({ lex: "1", type: TYPES.OPERAND, priority: 0 })
      this.postfix_.push({ lex: "+", type: TYPES.OPERATOR, priority: 0 })

      const lexem = { lex: `END_COND#${this.depth_}`, type: TYPES.LOOP, priority: 0 }
      this.postfix_.push(lexem)

      const jmp = { lex: `JMP`, type: TYPES.JMP_L, priority: 0 }
      this.postfix_.push(jmp)

      this.depth_--
      this.loopFrom_ = 0
      this.loopDepth_ = 0
      this.loopTo_ = 0
      this.loopVar_ = ''
    } else {
      const jmp = { lex: `EXIT#${this.loopDepth_}`, type: TYPES.JMP_L, priority: 0 }
      this.postfix_.push(jmp)
    }
  }

  handleOperator(lexem) {
    if (lexem.priority > this.peekOperators().priority) {
      this.operators_.push(lexem)
    } else {
      this.popOperators(lexem)
      this.operators_.push(lexem)
    }
  }

  openBracket(vtb) {
    const lexem = this.handleVtb(vtb, TYPES.OPEN_BRACKET, () => 0)
    this.operators_.push(lexem)
  }

  closeBracket() {
    while (this.operators_.length) {
      const lex = this.operators_.pop()
      if (lex.lex === "(") break
      this.postfix_.push(lex)
    }
  }

  popOperators(lexem) {
    while (this.operators_.length) {
      if (this.peekOperators().priority < lexem.priority || this.peekOperators().lex === "(") break
      const lex = this.operators_.pop()
      this.postfix_.push(lex)
    }
  }

  peekOperators = () => {
    return tracer.operators_[tracer.operators_.length - 1]
  }
}

var getPrior = (lex) => {
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
  }
}

var tracer = new Tracer()
