#include "module_6.h"

void partition(string pattern, bool tree, const char* fn)
{
    
    fstream file;
    vector<Node> partitions;
    if(tree)
    {
        string filename = fn;
        
        file.open(filename.c_str());
        
        if (!file.is_open()) 
        {
            file.open(filename.c_str(), ios::out);
        
            Node part;
            createNode(pattern, part);
            partitions.push_back(part);

            printToFile(part, file);
            //file << part;

            for(int i = 1; i < pattern.length(); i++) // i is number of partitions
            {                                         // per being found.
                Node newNode;
                split(i, part, newNode);
                partitionToFile(newNode, partitions, pattern, file);
            }
        }
        else
        {
            cout << pattern << " already computed.";
        }
    }
    else
    {
        istringstream tokens(pattern);
        string tmp;
        tokens >> tmp;
        
        while(tokens)
        {
            Node part;
            
            cout << "We got: " << tmp <<endl;
            if(partitions.size() == 0)
            {
                createNode(tmp, part);
                partitions.push_back(part);
            }
            else partitions[0] = addToNode(partitions[0], tmp);
            
            tokens >> tmp;
        }
    }
    print(partitions, pattern);
}

Node& addToNode(Node& node, string newPart)
{
    Bundle tmp;
    createBundle(tmp, newPart);
    node.part.push_back(tmp);
    setupDistinct(node);
    return node;
}

void partition(Node& part, vector<Node>& partitions, string pattern)
{        
    partitions.push_back(part);
    cout<<endl;
    print(part);
    
    for(int i = part.currentIndex + 1; i < pattern.length(); i++)
    {
        Node newNode;
        split(i, part, newNode);
        partition(newNode, partitions, pattern);
    }
}

void partitionToFile(Node& part, vector<Node>& partitions, string pattern, fstream& file)
{        
    partitions.push_back(part);
    cout<<endl;
    printToFile(part, file);
    
    for(int i = part.currentIndex + 1; i < pattern.length(); i++)
    {
        Node newNode;
        split(i, part, newNode);
        partitionToFile(newNode, partitions, pattern, file);
    }
}


void createNode(string pattern, Node& newNode)
{
    newNode.bun.pattern = pattern;
    newNode.bun.isReptition = false;
    newNode.bun.count = 1;
    newNode.bun.rank = newNode.bun.pattern.length() * newNode.bun.count;
    newNode.part.push_back(newNode.bun);
    newNode.distinct.push_back(newNode.bun);
    newNode.currentIndex = 0;
}

void createBundle(Bundle& tmpBun, string pattern)
{
    tmpBun.pattern = pattern;
    tmpBun.isReptition = false;
    tmpBun.count = 1;
    tmpBun.rank = tmpBun.pattern.length() *tmpBun.count;
}

void print(vector<Node>& collection, string pattern)
{
    cout << "\nThe partitions for " << pattern << " are:\n";
    for(int i = 0; i < collection.size(); i++)
    {
        cout << i + 1 <<". "; print(collection[i]); cout <<endl;
    }
}

void print(Node& node)
{
    for(int i = 0; i < node.part.size(); i++)
    {
        if(i == 0) cout << node.part[i].pattern;
        else cout << "-" << node.part[i].pattern;
    }
    cout << endl;
    
    for(int i = 0; i < node.distinct.size(); i++)
    {
        cout << "The weight of " << node.distinct[i].pattern << "(" << node.distinct[i].codeWord <<") is "
                << node.distinct[i].pattern.length() << " x " << node.distinct[i].count
                << " = " << node.distinct[i].rank << endl;
    }
}

void printToFile(Node& node, fstream& file)
{
    for(int i = 0; i < node.part.size(); i++)
    {
        if(i == 0) file << node.part[i].pattern;
        else file << "-" << node.part[i].pattern;
    }
    cout << endl;
    
    for(int i = 0; i < node.distinct.size(); i++)
    {
        file << "The weight of " << node.distinct[i].pattern << "(" << node.distinct[i].codeWord <<") is "
                << node.distinct[i].pattern.length() << " x " << node.distinct[i].count
                << " = " << node.distinct[i].rank << endl;
    }
}

void print(Bundle& word)
{
    cout << word.pattern;
}

Node& split(int index, Node& node, Node& newPart) 
{
    copyNode(node, newPart);
    Bundle partition = newPart.part[newPart.part.size() - 1];
    if(!partition.isReptition)
    {
        newPart.part[newPart.part.size() - 1].pattern = partition.pattern.substr(0, index - node.currentIndex);
        Bundle tmpBun;
        tmpBun.pattern = node.bun.pattern.substr(index);
        tmpBun.isReptition = false;
        tmpBun.count = 1;
        tmpBun.rank = tmpBun.count * tmpBun.pattern.length();

        newPart.part.push_back(tmpBun);
        newPart.currentIndex = index;
        setupDistinct(newPart);
    }
    return newPart;
}

void copyNode(Node& orig, Node& newNode){
    newNode.distinct = orig.distinct;
    newNode.part = orig.part;
    newNode.bun = orig.bun;
    newNode.currentIndex = orig.currentIndex;
}

void setupDistinct(Node& node)
{
    node.distinct.clear();

    for(int i = 0; i < node.part.size(); i++)
    {
        if(!contains(node, node.part[i])) 
        {
            node.part[i].rank = node.part[i].count * node.part[i].pattern.length();
            node.distinct.push_back(node.part[i]);
        }
    }
    sort(node);
    allocateSorted(node);
}

bool contains(Node& node, Bundle& bun)
{
    for(int i = 0; i < node.distinct.size(); i++)
    {
        if(node.distinct[i].pattern.compare(bun.pattern) == 0)
        {
            node.distinct[i].rank = ++node.distinct[i].count * node.distinct[i].pattern.length();
            return true;
        }
    }
    return false;
}

void sort(Node& node)
{
    vector<Bundle> sorted;
    vector<Bundle> tmpSorted;

    sorted.push_back(node.distinct.back()); node.distinct.pop_back();
    while(!node.distinct.empty())
    {
        Bundle tmpBun = node.distinct.back(); node.distinct.pop_back();

        while(!sorted.empty())
        {
            if(sorted.back().rank < tmpBun.rank)
            {
                tmpSorted.push_back(sorted.back()); sorted.pop_back();
            } else break;
        }

        sorted.push_back(tmpBun);

        while(!tmpSorted.empty())
        {
            sorted.push_back(tmpSorted.back()); tmpSorted.pop_back();
        }
    }

    node.distinct.clear();
    node.distinct = sorted;
}

void allocateSorted(Node& node)
{
    codeWords hoff = getHuffmanCodeWords_Memory(node.distinct.size(), 2);
    for(int i = 0; i < hoff.size(); i++)
    {
        node.distinct[i].codeWord = cwToString(hoff[hoff.size() - 1 -i]);
    }
}