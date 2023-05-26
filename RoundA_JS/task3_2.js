"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
var __asyncValues = (this && this.__asyncValues) || function (o) {
    if (!Symbol.asyncIterator) throw new TypeError("Symbol.asyncIterator is not defined.");
    var m = o[Symbol.asyncIterator], i;
    return m ? m.call(o) : (o = typeof __values === "function" ? __values(o) : o[Symbol.iterator](), i = {}, verb("next"), verb("throw"), verb("return"), i[Symbol.asyncIterator] = function () { return this; }, i);
    function verb(n) { i[n] = o[n] && function (v) { return new Promise(function (resolve, reject) { v = o[n](v), settle(resolve, reject, v.done, v.value); }); }; }
    function settle(resolve, reject, d, v) { Promise.resolve(v).then(function(v) { resolve({ value: v, done: d }); }, reject); }
};
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.TaskMain = void 0;
const process_1 = __importDefault(require("process"));
// how hard would a typescript refactor be?
// test server uses ES6 modules not commonJS modules.
function ReadStdin() {
    var _a, e_1, _b, _c;
    return __awaiter(this, void 0, void 0, function* () {
        process_1.default.stdin.setEncoding("utf-8");
        let all_input = "";
        try {
            for (var _d = true, _e = __asyncValues(process_1.default.stdin), _f; _f = yield _e.next(), _a = _f.done, !_a;) {
                _c = _f.value;
                _d = false;
                try {
                    const chunk = _c;
                    all_input += chunk;
                }
                finally {
                    _d = true;
                }
            }
        }
        catch (e_1_1) { e_1 = { error: e_1_1 }; }
        finally {
            try {
                if (!_d && !_a && (_b = _e.return)) yield _b.call(_e);
            }
            finally { if (e_1) throw e_1.error; }
        }
        return all_input;
    });
}
if (require.main === module) {
    // read from stdin if called from top level node.
    ReadStdin().then((text) => {
        TaskMain(text);
    });
}
else {
    ;
}
// min number of letters to delete in P to get I or IMPOSSIBLE.
// - len(P) < len(I) means IMPOSSIBLE.
// - always same number of letters deleted, so either IMPOSSIBLE or len(I) - len(P).
function SolveCase(I, P) {
    if (P.length < I.length) {
        return "IMPOSSIBLE";
    }
    let j = 0;
    for (let i = 0; i < P.length; ++i) {
        if (P[i] == I[j]) {
            ++j;
        }
    }
    return (j == I.length) ? (P.length - I.length) : "IMPOSSIBLE";
}
function TaskMain(text) {
    const lines = text.split("\n");
    const T = parseInt(lines[0], 10);
    for (let i = 1, t = 1; t <= T; ++t) {
        const I = lines[i++];
        const P = lines[i++];
        const Result = SolveCase(I, P);
        console.log(`Case #${t}: ${Result}`);
    }
}
exports.TaskMain = TaskMain;
// exports.TaskMain = TaskMain;
