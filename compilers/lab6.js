var ignoreLastWord;

var Tracer = class Tracer {
  constructor() {
    this.history_ = []
    this.rollbackPoint_ = []
  }

  getAll() {
    return this.history_.reduce((acc, cur) => `${acc} ${cur}`, "")
  }

  setHistory(history) {
    this.history_ = history
  }

  getHistory() {
    return this.history_
  }

  pushLexem(...lexs) {
    lexs.forEach((e) => this.history_.push(e))
  }

  pushRollbackPoint() {
    this.rollbackPoint_.push(this.history_.length)
  }

  rollback() {
    const len = this.rollbackPoint_.pop()
    let oldHistory = Array(this.history_.length - len)

    for (let i = oldHistory.length - 1; i >= 0; i--)
      oldHistory[i] = this.history_.pop()

    return oldHistory
  }
}

var CMDS_ = {
  JUMP: "jump",
  JUMP_ELSE: "jumpElse",
  RETURN: "return",
  SCOPE_IN: "scopeIn",
  SCOPE_OUT: "scopeOut",
}

var KEYS_ = {
  STACK: "stack",
}

var operatorStack = []
var operandStack = []
var operandCount = 0
var tmp = []
var depth = 0
var exits = []

var pushLexem = (...lexs) => tracer.pushLexem(...lexs)

var writeError = (msg) => {
  errors.push(`Error: ${msg}`)
  hasError = true
}

var writeInfo = () => {
  pushLexem('\n')
  debugMessages.forEach((msg) => pushLexem(`${msg}\n`))
  debugMessages = []

  pushLexem('\n')
  errors.forEach((msg) => pushLexem(`${msg}\n`))
  errors = []

  hasError = false
}

var peekStack = (stack) => stack[stack.length - 1]

var popStack = (stack, count) => {
  let popped = []
  for (let i = 0; i < count; i++) popped = [stack.pop(), ...popped]
  return popped
}

var getLabel = (label) => `#${label}_${peekStack(operandStack)}#`
var setLabel = (label) => pushLexem(getLabel(label))

var setJump = (label) => pushLexem(getLabel(label), CMDS_.JUMP)
var setJumpElse = (label) => pushLexem(getLabel(label), CMDS_.JUMP_ELSE)

var pushVar = (name) => pushLexem(`${name} ${peekStack()}`)
var pushHistory = (history) => tracer.setHistory([...tracer.getHistory(), ...history])

var pushExit = () => {
  exits.length === 0
    ? writeError('No exits or function declarations')
    : pushLexem(peekStack(exits), CMDS_.JUMP)
}

var pushBreakable = () => {
  operandStack.push(++operandCount)
  pushLexem(CMDS_.SCOPE_IN)
  exits.push(getLabel('Exit'))
}

var popBreakable = () => {
  setLabel('Exit')
  exits.pop()

  operandStack.pop()
  pushLexem(CMDS_.SCOPE_OUT)
}

var getPriority = (lex) => {
  if (!lex) return -1

  if (lex === '~') return 9
  if (lex === '!') return 8
  if (lex.match(/[%*\/]/g)) return 6
  if (lex.match(/[+-]/g)) return 5
  if (lex.match(/[><]=?/g)) return 4
  if (lex.match(/[!=]=?/g)) return 3
  if (lex === '&&') return 2
  if (lex === '||') return 1

  return 0
}

var handleOp = (op) => {
  while (operatorStack.length) {
    if (getPriority(peekStack(operatorStack)) >= getPriority(op)) {
      pushLexem(operatorStack.pop())
    }
    else {
      break
    }
  }

  operatorStack.push(op)
}

var handleUnaryOp = (op) => handleOp(op === '-' ? '~' : op)

var handleCloseBracket = () => {
  while (operatorStack.length) {
    if (peekStack(operatorStack) === '(') {
      operatorStack.pop()
      break
    } else {
      pushLexem(operatorStack.pop())
    }
  }
}

var freeOperatorStack = () => {
  while (operatorStack.length) {
    if (peekStack(operatorStack) === '(') {
      operatorStack.pop()
    } else {
      pushLexem(operatorStack.pop())
    }
  }
}

var Cycle = class Cycle {
  constructor() {
    this.counter_ = '';
    this.startValue_ = 0;
    this.endValue_ = 0;
    this.step_ = 1;
  }

  form(body) {
    pushHistory([this.counter_]);
    pushHistory([this.counter_, this.startValue_, "="]);

    setLabel("Condition");
    pushHistory([this.counter_, this.endValue_, "<="]);
    setJumpElse("Exit");

    pushHistory(body);

    pushHistory([this.counter_, this.counter_, this.step_, "+", "="]);
    setJump("Condition");

    popBreakable();
    this.step = 1;
  }
}

var tracer = new Tracer()
var cycle = new Cycle()

var clearAll = () => {
  operandCount = 0
  operandStack = []
  operatorStack = []
  tmp = []
  depth = 0
  exits = []

  tracer.history_ = []
  tracer.rollbackPoint_ = []

  cycle.counter_ = ''
  cycle.startValue_ = 0
  cycle.endValue_ = 0
  cycle.step_ = 1
}
