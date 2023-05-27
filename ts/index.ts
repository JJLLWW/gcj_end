import * as tree from "./tree.js";
import * as tok from "./token.js";

// how would unit-tests work?

const tokeniser = new tok.Tokeniser();
tokeniser.tokenise("902312326 +  213   + 321   ");

let root = new tree.TreeNode(0, tree.NodeType.Number);
const num = root.evaluate();
console.log(num);