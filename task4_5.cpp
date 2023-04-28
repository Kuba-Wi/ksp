#include <cassert>
#include <iostream>
#include <string>
#include <vector>

class Tree {
public:
    Tree(const std::string& name) : _name{name} {}

    ~Tree() {
        size_t size = _subTrees.size();
        for (size_t i = 0; i < size; ++i) {
            this->Del(0);
        }
    }

    Tree* AddSub(const std::string name) {
        _subTrees.emplace_back(new Tree{name});
        return _subTrees.back();
    }

    uint32_t GetSubCount() {
        return _subTrees.size();
    }

    uint32_t GetAllSubCount() {
        uint32_t count = _subTrees.size();
        for (auto& sub : _subTrees) {
            count += sub->GetAllSubCount();
        }
        return count;
    }

    void print(size_t indent) {
        for (size_t i = 0; i < indent; ++i) {
            std::cout << " ";
        }
        std::cout << _name << "\n";
        for (auto& sub : _subTrees) {
            std::cout << " ";
            sub->print(indent + 1);
        }
    }

    void print(size_t indent, bool printNumbers) {
        if (printNumbers) {
            this->print(indent, 0, "");
        } else {
            this->print(indent);
        }
    }

    void Del(size_t subIndex) {
        for (size_t i = 0; i < _subTrees[subIndex]->_subTrees.size(); ++i) {
            _subTrees[subIndex]->Del(i);
        }
        delete(_subTrees[subIndex]);
        _subTrees.erase(_subTrees.begin() + subIndex);
    }

private:
    void print(size_t indent, size_t index, std::string prefix) {
        for (size_t i = 0; i < indent; ++i) {
            std::cout << " ";
        }
        if (index > 0) {
            prefix += std::to_string(index) + ".";
            std::cout << prefix << " ";
        }
        std::cout << _name << "\n";
        for (size_t i = 0; i < _subTrees.size(); ++i) {
            std::cout << " ";
            _subTrees[i]->print(indent + 1, i + 1, prefix);
        }
    }

    std::string _name;
    std::vector<Tree*> _subTrees;
};

int main() {
    Tree* root = new Tree("tree name");
    Tree* galaz1 = root->AddSub("galaz 1");
    Tree* galaz2 = root->AddSub("galaz 2");
    Tree* galaz3 = root->AddSub("galaz 3");
    Tree* galaz1_1 = galaz1->AddSub("galaz 1.1");
    Tree* galaz2_1 = galaz2->AddSub("galaz 2.1");
    Tree* galaz2_2 = galaz2->AddSub("galaz 2.2");
    Tree* galaz2_1_2 = galaz2_1->AddSub("galaz 2.1.1");

    assert(root->GetSubCount() == 3);
    assert(galaz1->GetSubCount() == 1);
    assert(root->GetAllSubCount() == 7);

    root->print(0, true);

    root->Del(1);
    assert(root->GetSubCount() == 2);
    assert(root->GetAllSubCount() == 3);

    std::cout << "\n";
    root->print(0);

    delete(root);
}
