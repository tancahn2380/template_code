struct node {
	LL val;
	node *lch, *rch;
};

//数xを追加
node *insert(node *p, int x) {
	if (p == NULL) {
		node *q = new node;
		q->val = x;
		q->lch = q->rch = NULL;
		return q;
	}
	else {
		if (x < p->val)p->lch = insert(p->lch, x);
		else p->rch = insert(p->rch, x);
		return p;
	}
}

//値xを検索
bool find(node *p, int x) {
	if (p == NULL)return false;
	else if (x == p->val)return true;
	else if (x < p->val)return find(p->lch, x);
	else return find(p->rch, x);
}

//値xを削除
node *remove(node *p, int x) {
	if (p == NULL)return NULL;
	else if (x < p->val)p->lch = remove(p->lch, x);
	else if (x > p->val)p->rch = remove(p->rch, x);
	else if (p->lch == NULL) {
		node *q = p->rch;
		delete p;
		return q;
	}
	else if (p->lch->lch == NULL) {
		node *q = p->lch;
		q->rch = p->rch;
		delete p;
		return q;
	}
	else {
		node *q;
		for (q = p->lch; q->rch->rch != NULL; q = q->rch);
		node *r = q->rch;
		q->rch = r->lch;
		r->lch = p->lch;
		r->rch = p->rch;
		delete p;
		return q;
	}
}

node *root = NULL;

void inorder(node *p) {
	if(p->lch!=NULL)inorder(p->lch);
	cout << " " << p->val;
	if(p->rch!=NULL)inorder(p->rch);
}

void preorder(node *p) {
	cout << " " << p->val;
	if (p->lch != NULL)preorder(p->lch);
	if (p->rch != NULL)preorder(p->rch);
}