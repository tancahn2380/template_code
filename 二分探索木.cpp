class node {
public:
	int key;
	node *parent, *lch, *rch;
};

node *NIL, *root;

void insert(int v) {
	node *y = NIL, *x = root, *z = new node;
	z->key = v; z->lch = z->rch = NIL;
	while (x != NIL) {
		y = x;
		if (z->key < x->key)x = x->lch;
		else x = x->rch;
	}
	z->parent = y;
	if (y == NIL)root = z;
	else if (z->key < y->key)y->lch = z;
	else y->rch = z;
	return;
}

node* find(int k) {
	node *x = root;
	while (x != NIL&&k != x->key) {
		if (k < x->key)x = x->lch;
		else x = x->rch;
	}
	return x;
}

node* next(node *z) {
	node *x, *y;
	if (z->rch != NIL) {
		x = z->rch;
		while (x->lch != NIL)x = x->lch;
		return x;
	}

	y = z->parent;
	while (y != NIL&&x == y->rch) {
		x = y;
		y = y->parent;
	}
	return y;
}

void remove(node *z) {
	node *y, *x;
	if (z->lch == NIL || z->rch == NIL)y = z;
	else y = next(z);

	if (y->lch != NIL)x = y->lch;
	else x = y->rch;

	if (x != NIL)x->parent = y->parent;

	if (y->parent == NIL)root = x;
	else if (y == y->parent->lch)y->parent->lch = x;
	else y->parent->rch = x;

	if (y != z)z->key = y->key;
	delete(y);
	return;
}

void ino(node *u) {
	if (u == NIL)return;
	ino(u->lch);
	cout << " " << u->key;
	ino(u->rch);
	return;
}

void preo(node *u) {
	if (u == NIL)return;
	cout << " " << u->key;
	preo(u->lch);
	preo(u->rch);
	return;
}

void print() {
	ino(root);
	cout << endl;
	preo(root);
	cout << endl;
	return;
}

int main() {
	int n; cin >> n;
	string s; node *a;
	while (cin >> s) {
		if (s == "insert") {
			cin >> n;
			insert(n);
		}
		else if (s == "find") {
			cin >> n;
			a = find(n);
			if (a != NIL)cout << "yes" << endl;
			else cout << "no" << endl;
		}
		else if (s == "delete") {
			cin >> n;
			remove(find(n));
		}
		else if (s == "print")print();
	}
	return 0;
}