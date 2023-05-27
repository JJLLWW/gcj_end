import * as tree from "./tree.js";
import * as tok from "./token.js";

// how would unit-tests work?

const tokeniser = new tok.Tokeniser();
const toks = tokeniser.tokenise("902312326 +  213   + 321   ");
console.log(toks);

let root = new tree.TreeNode(0, tree.NodeType.Number);
const num = root.evaluate();
console.log(num);