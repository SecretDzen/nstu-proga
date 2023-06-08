var ignoreLastWord;

var idReg = /[a-z][0-9]{1,4}[a-z]/;
var binaryReg = /([+\-*^><=])|([&][&])|([|][|])|([!=><][=])/;
var unaryReg = /[mp!]/;
var actionReg = /[<][A-Z]+[>]/;
var markReg = /[A-Z]+[#][0-9]/;
var goMarkReg = /[A-Z]+[#][0-9][:]/;

var numReg = /[0-9]([.][0-9])*/;
var stringReg = /["][a-zA-Z]+["]/;

var ASM = class ASM {
  constructor(rpn) {
    this.rpn_ = rpn.split(" ");
    this.asm_ = []; // {label: '', code: '', op1: '', op2: ''}
    this.queue_ = [];
    this.label_ = null;
  }

  getAll() {
    this.form();
    const title = "\n\n=== ASM ===\n";
    const body = this.asmToVtb();

    return title + body;
  }

  asmToVtb() {
    let body = "";
    this.asm_.forEach((e) => {
      body += `${e.label} ${e.code} ${e.op1} ${e.op2}\n`;
    });
    return body;
  }

  form() {
    while (this.rpn_.length) {
      const item = this.rpn_.shift();

      if (item.match(actionReg)) {
        this.handleAction(item);
      } else if (item.match(binaryReg)) {
        this.handleBinary(item);
      } else if (item.match(goMarkReg)) {
        this.handleGoMark(item);
      } else {
        this.queue_.push(item);
      }
    }

    if (this.label_) {
      this.asm_.push({ label: this.label_, code: null, op1: null, op2: null });
    }
  }

  handleGoMark(goMark) {
    this.label_ = goMark;
  }

  handleBinary(code) {
    const label = this.useLabel();
    const [op1, op2] = this.useBinaryAction();
    const item = { label, code, op1, op2 };
    this.asm_.push(item);
  }

  handleAction(act) {
    const label = this.useLabel();

    if (act === "<FUNC>" || act === "<VAR>" || act === "<JMPF>") {
      const [op1, op2] = this.useBinaryAction();
      const item = { label, code: act, op1, op2 };
      this.asm_.push(item);
    } else {
      const op1 = this.useUnaryAction();
      const item = { label, code: act, op1, op2: null };
      this.asm_.push(item);
    }
  }

  useUnaryAction() {
    const op = this.queue_.shift() || "STACK";
    return op;
  }

  useBinaryAction() {
    const op1 = this.queue_.shift() || "STACK";
    const op2 = this.queue_.shift() || "STACK";

    return [op1, op2];
  }

  useLabel() {
    let label = null;
    if (this.label_) {
      label = this.label_;
      this.label_ = null;
    }
    return label;
  }

  peekAsm() {
    return this.asm_[this.asm_.length - 1];
  }
};

var RPN = class RPN {
  constructor() {
    this.rpn_ = [];
    this.stack_ = [];
    this.temp_ = [];
    this.depth_ = 0;

    this.funcCounter_ = 0;
    this.loopDepth_ = 0;
    this.isError = false;
  }

  clear() {
    this.rpn_ = [];
    this.stack_ = [];
    this.temp_ = [];
    this.depth_ = 0;

    this.funcCounter_ = 0;
    this.loopDepth_ = 0;
  }

  getAll() {
    const title = "=== RPN ===\n";
    if (this.isError) {
      return "Error while parsing";
    } else {
      const body = this.rpn_.join(" ");
      const asm = new ASM(body);
      return title + body + asm.getAll();
    }
  }

  operator(vtb, isUnary = false) {
    let op = vtb.currentLexem[1];
    if (isUnary) {
      op = op === "-" ? "m" : op;
      op = op === "+" ? "p" : op;
    }

    const pr = this.getPrior(op);

    if (this.stack_.length === 0) {
      this.stack_.push(op);
    } else {
      const stackOp = this.peekStack();
      const stackPr = this.getPrior(stackOp);

      if (pr > stackPr) {
        this.stack_.push(op);
      } else {
        this.popStack(pr);
        this.stack_.push(op);
      }
    }
  }

  operand(vtb) {
    const op = vtb.currentLexem[1];
    this.rpn_.push(op);
  }

  peekStack() {
    return this.stack_[this.stack_.length - 1];
  }

  pushStack(vtb) {
    const op = vtb.currentLexem[1];
    this.stack_.push(op);
  }

  popStack(pr) {
    while (this.stack_.length) {
      const stackOp = this.peekStack();
      const stackPr = this.getPrior(stackOp);

      if (stackPr === 50) break;
      if (pr > stackPr) break;

      this.rpn_.push(this.stack_.pop());
    }
  }

  openScope() {
    this.stack_.push("(");
  }

  closeScope() {
    this.popStack(0);
    this.stack_.pop();
  }

  action(name) {
    if (name === "arg") {
      this.popStack(0);
      this.rpn_.push("<ARG>");
    }

    if (name === "carg") {
      this.popStack(0);
      this.rpn_.push("<CARG>");
    }

    if (name === "call") {
      this.popStack(0);
      this.rpn_.push("<CALL>");
    }

    if (name === "ret") {
      this.popStack(0);
      this.rpn_.push("<RET>");
      this.rpn_.push("ENDFN#" + this.funcCounter_);
      this.rpn_.push("<JMP>");
    }

    if (name === "var") {
      this.popStack(0);
      this.rpn_.push("<VAR>");
    }

    if (name === "func") {
      this.popStack(0);
      this.rpn_.push("<FUNC>");
    }

    if (name === "funcL") {
      this.rpn_.push(`FN#${this.funcCounter_}:`);
    }

    if (name === "fnEnd") {
      this.rpn_.push(`ENDFN#${this.funcCounter_}:`);
      this.funcCounter_++;
    }

    if (name === "=") {
      this.popStack(0);
      this.rpn_.push("=");
    }

    if (name === "cond") {
      this.depth_++;
      this.popStack(0);
      this.rpn_.push("ELSE#" + this.depth_);
      this.rpn_.push("<JMPF>");
    }

    if (name === "else") {
      this.popStack(0);
      this.rpn_.push("END#" + this.depth_);
      this.rpn_.push("<JMP>");
      this.rpn_.push(`ELSE#${this.depth_}:`);
    }

    if (name === "end") {
      this.popStack(0);
      this.rpn_.push(`END#${this.depth_}:`);
      this.depth_--;
    }

    if (name === "rollback") {
      this.popStack(0);

      while (true) {
        let lex = this.rpn_[this.rpn_.length - 1];
        if (!lex || lex === `LOOP#${this.loopDepth_}:`) break;
        this.temp_.push(this.rpn_.pop());
      }
    }

    if (name === "loop") {
      this.depth_++;
      this.loopDepth_ = this.depth_;
      this.rpn_.push(`LOOP#${this.loopDepth_}:`);
    }

    if (name === "formLoop") {
      this.popStack(0);
      this.rpn_.push(`END#${this.loopDepth_}`);
      this.rpn_.push(`<JMPF>`);

      while (this.temp_.length) this.rpn_.push(this.temp_.pop());
      this.rpn_.push(`LOOP#${this.loopDepth_}`);
      this.rpn_.push(`<JMP>`);
      this.rpn_.push(`END#${this.loopDepth_}:`);
      this.depth_--;
    }

    if (name === "break") {
      if (this.depth_ === 0) {
        this.isError = true;
      }
      this.rpn_.push(`END#${this.loopDepth_}`);
      this.rpn_.push(`<JMP>`);
    }
  }

  getPrior(lex) {
    switch (lex) {
      case "<":
      case ">":
      case ">=":
      case "<=":
      case "!=":
        return 5;

      case "+":
      case "-":
        return 10;

      case "*":
      case "/":
        return 20;

      case "^":
        return 30;

      case "m":
      case "!":
      case "p":
        return 40;

      case "(":
        return 50;
    }
    return 0;
  }
};

var tracer = new RPN();
