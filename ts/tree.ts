// public/private members?
// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Classes/Private_class_fields

const types = ["expr", "val"];

// expression tree, operator may have child operators. (1 + 2) * (3 + 4).

// static func - staticmethod, #field is private field. extends for inheritance

// https://www.typescriptlang.org/docs/handbook/2/classes.html

export enum NodeType {
    Number,
    BinaryOp
}

// tree should be fully parenthesised so don't have to care about precedence.

// members should ideally be private.
// x | null awkward, probably a syntax shortcut.
export class TreeNode {
    left : TreeNode | null;
    right : TreeNode | null;
    val : number;
    type : NodeType;
    constructor(val : number, type : NodeType) {
        this.left = null;
        this.right = null;
        this.val = val;
        this.type = type;
    }
    evaluate() : number {
        switch(this.type) {
            case NodeType.Number:
                return this.val;
                break;
            case NodeType.BinaryOp:
                if(this.left == null || this.right == null) {
                    throw new Error("No node for binary operator argument.");
                }
                // for now hard code only operation as +.
                return this.left.evaluate() + this.right.evaluate();
                break;
        }
    }
}