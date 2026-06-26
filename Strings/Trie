struct Trie {
    struct Node {
        Node *children[26]; //every node has 26 children
        int prefix, End;

        Node() {
            prefix = End = 0;
            memset(children, 0, sizeof(children));
        }
    };

    Node *root = new Node();

    void insert(string &word) {
        Node *cur = root;
        for (auto i: word) {
            int ind = i - 'a';
            if (!cur->children[ind]) {
                //if you do not have this node create it
                cur->children[ind] = new Node();
            }
            cur = cur->children[ind]; //else keep down in the tree
            cur->prefix++; //how many times you reach this node as prefix
        }
        cur->End++; //how many word end with this character
    }

    int count(string &word) {
        Node *cur = root;
        for (auto i: word) {
            int ind = i - 'a';
            if (!cur->children[ind]) {
                return 0;
            }
            cur = cur->children[ind];
        }
        return cur->End;
    }

    void getWordsDFS(Node *node, string current_word, vector<string> &result,ll all) {
        // If End > 0, it means a word finishes at this node
        if (node->End > 0) {
            for (int i = 0; i < node->End - all; i++) {
                result.push_back(current_word);
            }
        }

        // Check all 26 possible children
        for (int i = 0; i < 26; i++) {
            if (node->children[i]) {
                // Append the character corresponding to index 'i' and continue DFS
                getWordsDFS(node->children[i], current_word + char(i + 'a'), result,0);
            }
        }
    }

    // Returns a vector of all strings starting with 'pat'
    vector<string> ret(string &pat) {
        vector<string> result;
        Node *cur = root;

        // Step 1: Navigate to the end of the prefix
        for (auto i: pat) {
            int ind = i - 'a';
            if (!cur->children[ind]) {
                return result; // Prefix doesn't exist, return empty vector
            }
            cur = cur->children[ind];
        }

        // Step 2: Run DFS from the prefix's ending node
        getWordsDFS(cur, pat, result, cur->End);

        return result;
    }

    bool exist(string &word) {
        Node *cur = root;
        for (auto i: word) {
            int ind = i - '0';
            if (!cur->children[ind]) {
                return 0;
            }
            cur = cur->children[ind];
            if (cur->End) {
                return 1;
            }
        }
        return 0;
    }
};
