#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <string>
#include <vector>

class TreeNode {
private:
    std::string type;
    std::string value;
    std::vector<TreeNode*> children;

public:
    TreeNode(const std::string& type, const std::string& value = "") 
        : type(type), value(value) {}

    static TreeNode* createNonTerminalNode(const std::string& type) {
        return new TreeNode(type);
    }

    static TreeNode* createTerminalNode(const std::string& type, const std::string& value = "") {
        return new TreeNode(type, value);
    }

    void addChild(TreeNode* child) {
        children.push_back(child);
    }

    const std::string& getType() const {
        return type;
    }

    const std::string& getValue() const {
        return value;
    }

    const std::vector<TreeNode*>& getChildren() const {
        return children;
    }

    int getNumChildren() const {
        return children.size();
    }


    void postOrderTraversal(std::ofstream& outFile, int depth = 0, bool isLast = false) {
        if (!children.empty()) {
            for (size_t i = 0; i < getNumChildren() - 1; ++i) {
                children[i]->postOrderTraversal(outFile, depth + 1, false);
            }
            children.back()->postOrderTraversal(outFile, depth + 1, true);
        }

        if (!value.empty()) {
            if (getNumChildren() > 0) {
                outFile << " ";
            }
            
            outFile << value;

            if (!isLast) {
                outFile << " ";
            } else {
                outFile << "\n" << std::string(depth, ' ');
            }
        }
        
    }


    ~TreeNode() {
        for (auto child : children) {
            delete child;
        }
    }
};

#endif  // TREE_NODE_H
