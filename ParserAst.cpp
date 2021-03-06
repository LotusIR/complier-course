#include "Lexer.h"
#include <string>

using namespace std;

const int layer_inc = 4;

string itoa(int x) {
	string res;
	while (x) {
		res += '0' + x%10;
		x /= 10;
	}
	reverse(res.begin(),res.end());
	return res;
}

class AstNode {
public:
	virtual void print(int layer = 0) {
		
	};
	
	virtual int calc() {
		return INT32_MIN;
	}

	virtual string gen(vector<string> &quards,int &tot) {
		return "t"+itoa(tot);
	}
};


class NumberAstNode: public AstNode  {
	public:
		int value;
		NumberAstNode(string & val) {
			value = atoi(val.c_str());
		}
		virtual void print(int layer = 0) {
			for (int i = 0; i < layer; ++i) cout << " ";
			cout << "-Number: " << value << '\n';
		}
		virtual int calc() {
			return value;
		}
		virtual string gen(vector<string> &quards,int &tot) {
			string curName = "t" + itoa(++tot);
			string str = "(:=,"+itoa(value)+",_,"+curName+")";
			quards.push_back(str);
			return curName;
		}
}; 

class IdentAstNode: public AstNode  {
	public:
		string identName;
		IdentAstNode(string & val) {
			identName = val;
		}
		virtual void print(int layer = 0) {
			for (int i = 0; i < layer; ++i) cout << " ";
			cout << "-Ident: " << identName << '\n';
		}
		virtual int calc() {
			cout << "Undefined ident: " << identName << "(calculated as 0)\n";
			return 0;
		}
		virtual string gen(vector<string> &quards,int &tot) {
			// string curName = "t" + itoa(++tot);
			// string str = "(:=,"+identName+",_,"+curName+")";
			// quards.push_back(str);
			return identName;
		}
};

class UniopAstNode: public AstNode  {
	public:
		AstNode *child;
		string op;
		UniopAstNode(AstNode *_child,const string &op_type):op(op_type),child(_child) {}

		virtual void print(int layer = 0) {
			for (int i = 0; i < layer; ++i) cout << " ";
			cout << "-UniOperator: " << op << '\n';
			child->print(layer+layer_inc);
		}

		virtual int calc() {
			switch (op[0])
			{
				case '+':
					return child->calc();
				case '-':
					return -child->calc();
			}
			return 0;
		}

		virtual string gen(vector<string> &quards,int &tot) {
			string cName = child->gen(quards,tot);
			string curName = "t"+itoa(++tot);
			string str;
			if (op == "+") {
				return cName;
			}
			else {
				str =  "(:=,-" + cName + ",_," + curName + ")";
			}
			quards.push_back(str);
			return curName;
		}

		~UniopAstNode() {
			delete child;
		}
};

class BinopAstNode: public AstNode  {
	public:
		AstNode *lchild,*rchild;
		string op;
		BinopAstNode(AstNode *_lchild,AstNode *_rchild,const string &op_type):op(op_type),lchild(_lchild),rchild(_rchild) {}

		virtual void print(int layer = 0) {
			for (int i = 0; i < layer; ++i) cout << " ";
			cout << "-BinOperator: " << op << '\n';
			lchild->print(layer+layer_inc);
			rchild->print(layer+layer_inc);
		}

		virtual int calc() {
			switch (op[0])
			{
				case '+':
					return lchild->calc()+rchild->calc();
				case '-':
					return lchild->calc()-rchild->calc();
				case '*':
					return lchild->calc()*rchild->calc();
				case '/': {
					int rvalue = rchild->calc();
					if (rvalue == 0) {
						throw new runtime_error("divided by 0");
					}
					else return lchild->calc()/rchild->calc();
				}
			}
			return 0;
		}

		virtual string gen(vector<string> &quards,int &tot) {
			string lname = lchild->gen(quards,tot);
			string rname = rchild->gen(quards,tot);
			string curName = "t"+itoa(++tot);
			string str = "("+op+","+lname+","+rname+","+curName+")";
			quards.push_back(str);
			return curName;
		}

		~BinopAstNode() {
			delete lchild;
			delete rchild;
		}
};



class Error {
public:
	string _type;
	string _msg;
	Error(const string &type, const string &msg) {
		this->_type = std::move(type);
		this->_msg = std::move(msg);
	}
	void print() {
		cout << _type << " " << _msg << '\n';
	}
};

vector<string> qgen(AstNode * root) {
	vector<string> res;
    int tot = 0;
    root->gen(res,tot);
	if (res.empty()) {
		string identName = root->gen(res,tot);
		string str = "(:=,"+identName+",_,"+"t1)";
		res.push_back(str);
	}
	return res;
}

class RecursiveDecsentParser {
public:
	unsigned int idx = 0;
	vector<Error *> errors;

	RecursiveDecsentParser() {};
	~RecursiveDecsentParser() {};

	void error(const string &type, const string &msg, const int &idx = 0) {
		this->errors.push_back(new Error(type, msg));
	}

	AstNode *parse(vector<token> &tokens) {
		AstNode* ans = this->E(tokens);
		if (!ans) {
			for (auto& err:errors) {
				err->print();
			}
		}
		return ans;
	}

	AstNode *E(vector<token> &tokens) {
		AstNode *match_NoneTerm_T = this->T(tokens);
		if (match_NoneTerm_T == nullptr) {
			return nullptr;
		}
		AstNode *result = match_NoneTerm_T;
		while (true) {
			if (tokens[this->idx].type == token_type::plus) {
				this->idx++;
				AstNode *match_NoneTerm_T = this->T(tokens);
				if (match_NoneTerm_T == nullptr) {
					return nullptr;
				}
				else {
					result = new BinopAstNode(result,match_NoneTerm_T,"+");
				}
			}
			else if (tokens[this->idx].type == token_type::minus) {
				this->idx++;
				AstNode *match_NoneTerm_T = this->T(tokens);
				if (match_NoneTerm_T == nullptr) {
					return nullptr;
				}
				else {
					result = new BinopAstNode(result,match_NoneTerm_T,"-");
				}
			}
			else break;
		}
		return result;
	}

	AstNode *T(vector<token> &tokens) {
		AstNode *match_NoneTerm_A = this->A(tokens);
		if (match_NoneTerm_A == nullptr) {
			return nullptr;
		}
		AstNode *result = match_NoneTerm_A;
		while (true) {
			if (tokens[this->idx].type == times) {
				this->idx++;
				AstNode *match_NoneTerm_A = this->A(tokens);
				if (match_NoneTerm_A == nullptr) {
					return nullptr;
				}
				else {
					result = new BinopAstNode(result,match_NoneTerm_A,"*");
				}
			}
			else if (tokens[this->idx].type == slash) {
				this->idx++;
				AstNode *match_NoneTerm_A = this->A(tokens);
				if (match_NoneTerm_A == nullptr) {
					return nullptr;
				}
				else {
					result = new BinopAstNode(result,match_NoneTerm_A,"/");
				}
			}
			else break;
		}
		return result;
	}

	AstNode *A(vector<token> &tokens) {
		if (tokens[this->idx].type == token_type::plus) {
			this->idx++;
			AstNode *match_NoneTerm_F = this->F(tokens);
			if (match_NoneTerm_F == nullptr) {
				return nullptr;
			}
			AstNode *node = new UniopAstNode(match_NoneTerm_F,"+");
			return node;
		}
		else if (tokens[this->idx].type == token_type::minus) {
			this->idx++;
			AstNode *match_NoneTerm_F = this->F(tokens);
			if (match_NoneTerm_F == nullptr) {
				return nullptr;
			}
			AstNode *node = new UniopAstNode(match_NoneTerm_F,"-");
			return node;
		}
		else {
			AstNode *match_NoneTerm_F = this->F(tokens);
			if (match_NoneTerm_F == nullptr) {
				return nullptr;
			}
			return match_NoneTerm_F;
		}
	}

	AstNode *F(vector<token> &tokens) {
		if (tokens[this->idx].type == number) {
			AstNode *node = new NumberAstNode(tokens[this->idx].text);
			this->idx++;
			return node;
		}
		else if (tokens[this->idx].type == ident) {
			AstNode *node = new IdentAstNode(tokens[this->idx].text);
			this->idx++;
			return node;
		}
		else if (tokens[this->idx].type == lparen) {
			this->idx++;
			AstNode *match_NoneTerm_E = this->E(tokens);
			if (match_NoneTerm_E == nullptr) {
				return nullptr;
			}
			if (tokens[this->idx].type == rparen) {
				this->idx++;
				return match_NoneTerm_E;
			}
			ofstream ofs("in_parser_result.txt");
			utils::err_unex_token(ofs,tokens,idx,Lexer::getDef(),"')'");
			// this->error("UnexpectedError", "expect ')' but no valid found", idx);
			return nullptr;
		}
		ofstream ofs("in_parser_result.txt");
		utils::err_unex_token(ofs,tokens,idx,Lexer::getDef(),"'??????'/'?????????'/'('");
		return nullptr;
	}
};
