// 23 + 34 + 1 + 45 + 89. ignore parentheses otherwise involved.
// 23+12354+36723.
// 1) remove all whitespace.
// 2) if detect character not [0-9] or + then bug out.
// 3) now sequences of digits are numbers, anything else is an operator.
// Map strings like "+" to an operator.
// 4) have all ops and all nums, validate / parse both, then join arrays.

// as all operators binary have num op num op num op num.

export enum TokenType {
    Number,
    BinOp
}

export enum BinOpType {
    Add
}

export class Token {
    Type : TokenType;
    NumVal : number | null = null;
    OpType : BinOpType | null = null;
    constructor(type : TokenType, val : number | BinOpType) {
        this.Type = type;
        switch(type) {
            case TokenType.Number:
                this.NumVal = val;
                break;
            case TokenType.BinOp:
                this.OpType = val;
                break;
        }
    }
}

export class Tokeniser {
    readonly Whitespace : RegExp;
    readonly Valid : RegExp;
    constructor() {
        this.Whitespace = /\s/g;
        this.Valid = /^[0-9+]+$/;
    }
    tokenise(line : string) : Token[] {
        line = line.replace(this.Whitespace, "");
        if(!this.Valid.test(line)) {
            throw Error("line contains unexpected character");
        }
        const Nums = line.split(/[^0-9]+/);
        const NonNums = line.split(/[0-9]+/);
        const NumTokens = this.processNums(Nums);
        const OpTokens = this.processNonNums(NonNums);
        let Tokens = [];
        for(let i=0; i<OpTokens.length; ++i) {
            Tokens.push(NumTokens[i]);
            Tokens.push(OpTokens[i]);
        }
        Tokens.push(NumTokens[NumTokens.length - 1]);
        return Tokens;
    }
    processNums(Nums : string[]) : Token[] {
        let NumTokens : Token[] = [];
        Nums.forEach((num : string) => {
            const val = parseInt(num);
            const tok = new Token(TokenType.Number, val);
            NumTokens.push(tok);
        });
        return NumTokens;
    }
    processNonNums(NonNums : string[]) : Token[] {
        if(NonNums[0] !== '') {
            throw Error("leading operator");
        }
        if(NonNums[NonNums.length - 1] !== '') {
            throw Error("trailing operator");
        }
        NonNums.shift(); // remove first elem
        NonNums.pop(); // remove last elem.
        let NonNumTokens : Token[] = [];
        NonNums.forEach((nonnum : string) => {
            if(nonnum.length > 1) {
                throw Error("multi character operator not supported");
            }
            switch (nonnum[0]) {
                case '+':
                    const tok = new Token(TokenType.BinOp, BinOpType.Add);
                    NonNumTokens.push(tok);
                    break;
                default:
                    throw Error("unrecognised operator");
            }
        })
        return NonNumTokens;
    }
}