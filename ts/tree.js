// public/private members?
// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Classes/Private_class_fields

const types = ["expr", "val"];

// expression tree, operator may have child operators. (1 + 2) * (3 + 4).

// why does typescript complain about the this in the class definition?

// static func - staticmethod, #field is private field. extends for inheritance

// https://www.typescriptlang.org/docs/handbook/2/classes.html

export class TreeNode {
    constructor(val, type) {
        this.left = null;
        this.right = null;
        this.val = val;
        this.type = type; // enum?
    }
    // python-esque, prefix with this yuck.
    evaluate() {
        // case statement?
        if(this.type === "val") {
            return this.val;
        } else if(this.type === "expr") {
            if(this.left == null || this.right == null) {
                return undefined;
            } else {
                return this.left.evaluate() + this.right.evaluate();
            }
        }
    }
}