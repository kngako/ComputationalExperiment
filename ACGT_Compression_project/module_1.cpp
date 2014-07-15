//COMPRESSION PROJECT: MODULE 1 HUFFMAN CODE GENERATOR: module_1.cpp
//Created by Mathys Ellis 31/01/2013

#include "module_1.h"
#include "module_6.h"

codeWords generateHuffmanCodeWordsI_CW(int noOfCodeWords, bool firstCode)
{
	codeWords temp;
	temp.resize(noOfCodeWords);

	//Loop throught each code word
	for(int i = 0; i < noOfCodeWords; i++)
	{
        //First value generated is always the firstCode value
		if (i == 0)
		{
			temp[i].push_back(firstCode);
		}
		//Last value generated is always same length as the prior value but has a firstCode at the end
		else if (i == (noOfCodeWords - 1))
		{
			temp[i].push_back(!firstCode);
			for(int x = 1; x < noOfCodeWords - 1; x++)
			{
				temp[i].push_back(firstCode);
			}
		}
		//The values generated inbetween always have the same length as (i + 1) but the start and end bits are !firstCode
		else
		{
			temp[i].push_back(!firstCode);
			for(int x = 1; x <= i - 1; x++)
			{
				temp[i].push_back(firstCode);
			}
			temp[i].push_back(!firstCode);
		}
	}

	return temp;
}

bitstream generateHuffmanCodeWordsI_BS(int noOfCodeWords, bool firstCode)
{
	bitstream temp;

	//Loop throught each code word
	for(int i = 0; i < noOfCodeWords; i++)
	{
		//First value generated is always the firstCode value
		if (i == 0)
		{
			temp.push_back(firstCode);
		}
		//Last value generated is always same length as the prior value but has a firstCode at the end
		else if (i == (noOfCodeWords - 1))
		{
			temp.push_back(!firstCode);
			for(int x = 1; x < noOfCodeWords - 1; x++)
			{
				temp.push_back(firstCode);
			}
		}
		//The values generated inbetween always have the same length as (i + 1) but the start and end bits are !firstCode
		else
		{
			temp.push_back(!firstCode);
			for(int x = 1; x <= i - 1; x++)
			{
				temp.push_back(firstCode);
			}
			temp.push_back(!firstCode);
		}
	}

	return temp;
}

codeWords generateHuffmanCodeWordsR_CW(int noOfCodeWords, bool firstCode)
{
	codeWords temp;

	int toplevel = (int) ((log10l(noOfCodeWords)/log10l(2)) + 1);
	int total = (int) (powl(2,(double)toplevel));

	int noOnPreLevel = total - noOfCodeWords;

	int codeWordCount = 0;

	recDownCodeWords(toplevel, noOfCodeWords - noOnPreLevel, noOfCodeWords, 0, codeWordCount, temp, *(new codeWord), false);

	return temp;

}

void recDownCodeWords(int levels, int noInTopLevels, int noOfCW, int countLevel, int& codeWordCount, codeWords& cws, codeWord curCW, bool side)
{
	if(codeWordCount < noInTopLevels)
	{
		if(countLevel < levels)
		{
			if(countLevel > 0)
			{
				curCW.push_back(side);
			}
			countLevel++;
			//Left and right side
			recDownCodeWords(levels, noInTopLevels, noOfCW, countLevel,codeWordCount,cws,curCW,0);
			recDownCodeWords(levels, noInTopLevels, noOfCW, countLevel,codeWordCount,cws,curCW,1);
		}
		else
		{
			curCW.push_back(side);
			cws.push_back(curCW);
			codeWordCount++;
		}
	}
	else if (codeWordCount < noOfCW)
	{
		if(countLevel < levels - 1)
		{

			if(countLevel > 0)
			{
				curCW.push_back(side);
			}
			countLevel++;
			//Left and right side
			recDownCodeWords(levels, noInTopLevels, noOfCW, countLevel,codeWordCount,cws,curCW,0);
			recDownCodeWords(levels, noInTopLevels, noOfCW, countLevel,codeWordCount,cws,curCW,1);
		}
		else
		{
			curCW.push_back(side);
			cws.push_back(curCW);
			codeWordCount++;
		}
	}

	return;
}

void recDownCodeWords_File(unsigned long long int levels, unsigned long long int noInTopLevels, unsigned long long int noOfCW, unsigned long long int countLevel, unsigned long long int& codeWordCount, fstream& outFile, codeWord curCW, bool side)
{
	if(codeWordCount < noInTopLevels)
	{
		if(countLevel < levels)
		{
			if(countLevel > 0)
			{
				curCW.push_back(side);
			}
			countLevel++;
			//Left and right side
			recDownCodeWords_File(levels, noInTopLevels, noOfCW, countLevel,codeWordCount,outFile,curCW,0);
			recDownCodeWords_File(levels, noInTopLevels, noOfCW, countLevel,codeWordCount,outFile,curCW,1);
		}
		else
		{
			curCW.push_back(side);
                        char* ptr = cwToString(curCW);
			outFile << ptr;
                        
                        delete [] ptr;
			codeWordCount++;

			if(codeWordCount < noOfCW)
			{
				//outFile << ",";
                                outFile << " ";
			}
		}
	}
	else if (codeWordCount < noOfCW)
	{
		if(countLevel < levels - 1)
		{

			if(countLevel > 0)
			{
				curCW.push_back(side);
			}
			countLevel++;
			//Left and right side
			recDownCodeWords_File(levels, noInTopLevels, noOfCW, countLevel,codeWordCount,outFile,curCW,0);
			recDownCodeWords_File(levels, noInTopLevels, noOfCW, countLevel,codeWordCount,outFile,curCW,1);
		}
		else
		{
			curCW.push_back(side);
                        char* ptr = cwToString(curCW);
                        
			outFile << ptr;
                        delete [] ptr;
                        
			codeWordCount++;                        
                        cout << "Generated: " << codeWordCount << '\r';
			if(codeWordCount < noOfCW)
			{
				outFile << " ";
                            //outFile << ",";
			}

		}
	}

	return;
}


codeWord getCodeWord(int noOfCodeWords, bool firstCode, int index)
{
	codeWord temp;
	
	//First value generated is always the firstCode value
	if (index == 1)
	{
		temp.push_back(firstCode);
	}
	//Last value generated is always same length as the prior value but has a firstCode at the end
	else if (index == noOfCodeWords)
	{
		temp.push_back(!firstCode);
		for(int x = 1; x < noOfCodeWords - 1; x++)
		{
			temp.push_back(firstCode);
		}
	}
	//The values generated inbetween always have the same length as (i + 1) but the start and end bits are !firstCode
	else
	{
		temp.push_back(!firstCode);
		for(int x = 1; x <= index - 2; x++)
		{
			temp.push_back(firstCode);
		}
		temp.push_back(!firstCode);
	}
		
	return temp;
}

codeWord getCodeWord_FromFile(const char* path, unsigned long long int m, unsigned long long int codewordIndex)
{
    char* filename = new char[STD_NUMBER_OF_CHARS];
    sprintf(filename,"%s%llu.%s", path,m, HUFFMAN_FILE_EXT);
    
    char* data = getLine_FromFile(filename,1);
    
    delete [] filename;
    
    codeWord temp;
    
    if(data != NULL)
    {    
        temp = findCodeWordInString(data, codewordIndex);

        delete [] data;
    }
    
    return temp;
}

codeWords getAllCodewords_FromFile(const char* path, unsigned long long int m)
{
    char* filename = new char[STD_NUMBER_OF_CHARS];
    sprintf(filename,"%s%llu.%s", path,m, HUFFMAN_FILE_EXT);

    char* data = getLine_FromFile(filename,1);
    
    delete [] filename;
    
    codeWords temp;
    
    if(data != NULL)
    {    
        temp = getAllCodeWordsInString(data);
        
        delete [] data;
    }
    
    return temp;
}

codeWords getHuffmanCodeWords_Memory(int m, int series)
{
	if (series == 1)
	{
		return generateHuffmanCodeWordsI_CW(m, true);
	}
	else
	{
		return generateHuffmanCodeWordsR_CW(m, true);
    }
}

bool getHuffmanCodeWords_File(const char* filename, unsigned long long int m, int series)
{
	fstream outputFile;
        
	outputFile.open(filename,ios::out);

	codeWord temp;

	bool firstCode = true;
        
        
	for(unsigned long long int j = m; j <= m; j++)
	{
                //cout << "Huffman codewords for m = " << j << endl;
                outputFile << j << " ";
                //outputFile << "{m:" << j << ",data:[";

		if (series == 1)
		{

			//Loop throught each code word
			for(int i = 0; i < j; i++)
			{
				//First value generated is always the firstCode value
				if (i == 0)
				{
					temp.push_back(firstCode);
				}
				//Last value generated is always same length as the prior value but has a firstCode at the end
				else if (i == (j - 1))
				{
					temp.push_back(!firstCode);
					for(int x = 1; x < j - 1; x++)
					{
						temp.push_back(firstCode);
					}
				}
				//The values generated inbetween always have the same length as (i + 1) but the start and end bits are !firstCode
				else
				{
					temp.push_back(!firstCode);
					for(int x = 1; x <= i - 1; x++)
					{
						temp.push_back(firstCode);
					}
					temp.push_back(!firstCode);
				}

				outputFile << cwToString(temp);
				if(i < j - 1)
				{
                                    outputFile << " ";
                                    //outputFile << ",";
				}

				temp.clear();
			}
		}
		else
		{
			unsigned long long int toplevel = (unsigned long long int) ((log10l(j)/log10l(2)) + 1);
			unsigned long long int total = (unsigned long long int) (powl(2,toplevel));

			unsigned long long int noOnPreLevel = total - j;

			unsigned long long int codeWordCount = 0;
                        
                        cout << "Number of codewords to generate: " << j << endl;
                        codeWord* tempCW = new codeWord;
                        
			recDownCodeWords_File(toplevel, j - noOnPreLevel, j, 0, codeWordCount, outputFile, *tempCW, false);
                        
                        delete tempCW;
                        
                        cout << endl;
		}
                outputFile << endl;
		//outputFile << "]}" << endl;

	}

	outputFile.close();

	return true;
}

/******************************************************************************
 **************************** Huffman generation ******************************
 ******************************************************************************/

vector<codeWords> generateAllHuffmanCodeWordsI_CW(int noOfCodeWords, bool firstCode)
{
    vector<codeWords> store;
    
    noOfCodeWords--; // Turn it into the number of internal nodes
    int* treeArray = new int[(2 * noOfCodeWords) + 1];
    int i = 0;
    
    for(; i < noOfCodeWords; i++)
    {
        treeArray[i] = 1;
    }
    
    for(int j = 0; j < (noOfCodeWords+1); j++)
    {
        treeArray[i++] = 0;
    }
    
    output_all_possible_trees(treeArray, noOfCodeWords, 0, 0, store);
                
    delete [] treeArray;
    return store;
}

void addCodeWords(vector<codeWords>& store, codeWords& cW)
{
    if(!contains(store, cW))
        store.push_back(cW);
}

bool contains(vector<codeWords>& store, codeWords cW)
{
    for(int i = 0; i < store.size(); i++)
    {
        if(equalLength(store[i], cW))
        {
            return true;
        }
    }
    return false;
}

bool equalLength(codeWords a, codeWords b)
{
    for(int i = 0; i < a.size() && i < b.size(); i++)
    {
        if(a[i].size() != b[i].size())
            return false;
    }
    return a.size() == b.size() ? true : false;
}

// rebuild the tree from a sequence such as "11000"
Node* rebuild_tree(int* s, int n)
{
    Node* root = createNode(0);
    stack<Node*> stk;
    stk.push(root);
    for(int i=1; i < n; i++)
    {
        if(s[i])
        {
            Node* node = createNode(0);
            if(s[i-1]) 
            {
                stk.top()->left = node;           
            }
            else
            {
                stk.top()->right = node;
                stk.pop();          
            }
            stk.push(node);
        }
        else 
        {
            if(!s[i-1]) stk.pop();
        }
    }

    return root;
}

//print all possible trees
void output_all_possible_trees(int* seq, int n, int num1, int num0, vector<codeWords>& store)
{
    if((num1 + num0) == 2*n)
    {
        seq[2*n] = 0;
        Node *root = rebuild_tree(seq, 2*n+1);
        //displayTree(root, 0);
        //show(seq, n);
        codeWords temp = codeWordsFromTree(root, n, true);
        //store.push_back(temp);
        addCodeWords(store, temp);
        return;
    }
        
    if(num1 >= num0 && num1 < n)
    {
        seq[num1+num0] = 1;
        output_all_possible_trees(seq, n, num1+1, num0, store); 
    }       
    
    if(num0 < num1 && num1 <=n)
    {
        seq[num1+num0] = 0;
        output_all_possible_trees(seq, n, num1, num0+1, store);
    }
}

void show(int* seq, int n)
{
    for(int i = 0; i < 2*n+1; i++)
    {
        cout << seq[i] << ", " ;
    }
    cout << endl;
}
void show(codeWords temp)
{
    for(int k = 0; k < temp.size(); k++)
    {
        for(int j = 0; j < temp[k].size(); j++)
        {
            cout << temp[k][j];
        }
        cout << ", ";
    }
    cout << endl;
}

Node* constructTree(int size)
{
    Node* root = createNode(1);
    for(int i = 1; i < size; i++)
    {
        insert(i+1,  root);
    }
    return root;
}

Node* createNode(int item)
{
    Node* node = new Node;

    node->item = item;
    node->left = NULL;
    node->right = NULL;

    return node;
}

Node* insert(int item, Node* node)
{
    if (node == NULL)
    {
        node = createNode(item);
        if (node == NULL)
            printf("%d not inserted, no memory available.\n", item);
    }
    else if (item < node->item)
        node->left = insert(item, node->left);
    else
        node->right = insert(item, node->right);
    return node;
}

Node* splay(Node* root)
{
    return rotate(NULL, root, root->right);
}

Node* rotate(Node* gr, Node* par, Node* ch)
{
    if (par->left == ch) 
    {
        return rotateRight(gr, par, ch);
    } 
    else 
    {
        return rotateLeft(gr, par, ch);
    }
}

Node* rotateLeft(Node* gr, Node* oldRoot, Node* ch)
{
    Node* par = parent(ch, oldRoot);
    par->right = ch->left;

    ch->left = oldRoot;
    return ch;
}

Node* rotateRight(Node* gr, Node* oldRoot, Node* ch)
{
    Node* par = parent(ch, oldRoot);
    par->left = ch->right;

    ch->left = oldRoot;
    return ch;
}

Node* parent(Node* node, Node* subTreeRoot)
{
    if(subTreeRoot->left == node || subTreeRoot->right == node) return subTreeRoot;
    
    if(node->item > subTreeRoot->item) return parent(node, subTreeRoot->right);
    else return parent(node, subTreeRoot->left);
}

void displayTree(Node *root, int depth)
{
    if (root == NULL) {
        padding (' ', depth);
        printf("-\n");
    }
    else 
    {
        displayTree(root->right, depth+1);
        padding(' ', depth);
        printf ( "%d\n", root->item);
        displayTree(root->left, depth+1);
    }
}

void padding(char ch, int n)
{
    for (int i = 0; i < n; i++)
        printf("%c%c%c%c", ch, ch, ch, ch);
}

codeWords codeWordsFromTree(Node* root, int noOfCodeWords, bool firstCode)
{
    codeWords temp;
    //temp.resize(noOfCodeWords);
    codeWord codeWord;
    
    return cwFromTree(root, codeWord, temp, firstCode);
}

codeWords sort(codeWords cW)
{
    codeWords sorted;
    if(cW.size() == 0) return sorted;

    sorted.push_back(cW.back()); cW.pop_back();
    while(!cW.empty())
    {
        codeWords tmp;
        while(!sorted.empty() && sorted.back().size() > cW.back().size())
        {
            tmp.push_back(sorted.back()); sorted.pop_back();
        }

        sorted.push_back(cW.back()); cW.pop_back();

        while(!tmp.empty())
        {
            sorted.push_back(tmp.back()); tmp.pop_back();
        }
    }
    
    return sorted;
}

codeWords cwFromTree(Node* node, codeWord& cW, codeWords& cWs, bool firstCode)
{
    if(node == NULL)
    {
        cWs.push_back(cW);
    }
    else
    {
       codeWord cW2;
       for(int i = 0; i < cW.size(); i++)
       {   
            cW2.push_back(cW[i]);
       }

       cW.push_back(firstCode);
       cwFromTree(node->left, cW, cWs, firstCode);

       cW2.push_back(!firstCode);
       cwFromTree(node->right, cW2, cWs, firstCode);
    }
    return sort(cWs);
}

Node* copy(Node* oldRoot)
{
    Node* newRoot = createNode(oldRoot->item);

    copyOver(newRoot, oldRoot->left);
    copyOver(newRoot, oldRoot->right);
    
    return newRoot;
}

Node* copyOver(Node* newSubTree, Node* oldSubTree)
{
    if(oldSubTree != NULL)
    {
        insert(oldSubTree->item, newSubTree);
        if(oldSubTree->item < newSubTree->item)
        {
            copyOver(newSubTree->left, oldSubTree->left);
            copyOver(newSubTree->left, oldSubTree->right);
        }
        else
        {
            copyOver(newSubTree->right, oldSubTree->left);
            copyOver(newSubTree->right, oldSubTree->right);
        }
    }

    return newSubTree;
} 

void processTree(Node* root, int noOfCodeWords, bool firstCode, vector<codeWords>& store)
{
    int unique = noOfCodeWords/2;
    int rDepth = rightmostDepth(root);

    for(int i = 1;i < rDepth; i++)
    { 
        Node* rootCopy = copy(root);

        Node* newRoot = rotate(NULL, rootCopy, rightmostAtDepth(rootCopy, i));

        codeWords temp = codeWordsFromTree(newRoot, noOfCodeWords, firstCode);
        show(temp);
        store.push_back(temp);
        
        processTree(newRoot, noOfCodeWords, firstCode, store);
        destoryTree(newRoot);
    }
}

int rightmostDepth(Node* root)
{
    return rightmostDepth(root, 0);
}

int rightmostDepth(Node* node, int depth)
{
    if(node == NULL) return depth;
    else return rightmostDepth(node->right, depth + 1);
}

Node* rightmostAtDepth(Node* root, int depth)
{
    return rightmostAtDepth(root->right, depth, 1);
}

Node* rightmostAtDepth(Node* node, int depthRequired, int depth)
{
    if(depth == depthRequired) return node;
    else return rightmostAtDepth(node->right, depthRequired, depth + 1);
}

void destoryTree(Node* node)
{
    if(node != NULL)
    {
        destoryTree(node->left);
        destoryTree(node->right);
        delete node;
    }
}

/******************************************************************************
**********************    HuffmanOptimally      *******************************
*******************************************************************************/

codeWords generateOptimalHuffmanCodeWords(partitionedString pStrings, bool firstCode)
{
    partitionedString distinct = distinction(pStrings);
    
    vector<codeWords> store = generateAllHuffmanCodeWordsI_CW(distinct.size(), firstCode);
    codeWords minCW = store[0];
    int bestBits = calculateBits(pStrings, distinct, minCW);
    
    for(int i = 1; i < store.size(); i++)
    {
        int bits = calculateBits(pStrings, distinct, store[i]);
        if(bits < bestBits)
        {
            bestBits = bits;
            minCW = store[i];
        }
    }
    
    cout << "For " ;
    print(pStrings);
    cout << "We get these Huffman trees...\n";
    for(int i = 0; i < store.size(); i++)
    {
        cout << i + 1 << ": " ;
        show(store[i]);
    }
    
    cout << "The best: ";
    show(minCW);
    
    cout << "With a size of: " << bestBits << endl;
    return minCW;
    /*partitionedString pS = distinction(pStrings);

    int total = pStrings.size();
    
    vector<HuffmanNode*> set;
    
    for(int i = 0; i < pS.size(); i++)
    {
        set.push_back(createHuffmanNode(pS[i]->frequency/(total*1.0), pS[i]->partitionStr, NULL, NULL));
    }

    while(set.size() > 1)
    {
        merge(getTwoSmallestPercentageNodeIndexes(set), set);
    }

    return codeWordsFromTree(set[0], pS.size(), firstCode);*/
}

int calculateBits(partitionedString& pStrings, partitionedString& distinct, codeWords cW)
{
    // (: + comma) + (encoded string size)
    int count = (distinct.size() * 3); 
    //cout << "*" << count << " via: (" << distinct.size() << "* 3) + (" << pStrings.size() << " * " << distinct.size() << ")" << endl;
    // Calculate how much each distinct string cost...
    for(int i = 0; i < distinct.size(); i++)
    {
        count += strlen(distinct[i]->partitionStr) * 3;
    }
    
    // Calculate the bits for the encoded string...
    for(int i = 0; i < pStrings.size(); i++)
    {
        count += cW[pStrings[i]->huffmanCWIndex].size();
    }
    
    return count;
}

partitionedString distinction(partitionedString& pString)
{
    partitionedString nPS;
    
    for(int i = 0; i < pString.size(); i++)
    {
        add(pString[i], nPS);
    }
    
    return nPS;
}

void add(partition* part, partitionedString& pString)
{
    for(int i = 0; i < pString.size(); i++)
    {
        if(strcmp(pString[i]->partitionStr, part->partitionStr) == 0)
        {
            pString[i]->frequency++;
            return;
        }
    }
    part->frequency = 1;
    pString.push_back(part);
}

void merge(int* smallest, vector<HuffmanNode*>& set)
{
    HuffmanNode* hNode = createHuffmanNode(
        set[smallest[0]]->percentage + set[smallest[1]]->percentage, 
        "***", set[smallest[0]], set[smallest[1]]);
        
    removeHuffmanNodes(set[smallest[0]], set[smallest[1]], set);
    set.push_back(hNode);
}

void removeHuffmanNodes(HuffmanNode* hNode1, HuffmanNode* hNode2, vector<HuffmanNode*>& set)
{  
    int count = 0;
    vector<HuffmanNode*> tmp;
    HuffmanNode* tNode;// = set.pop_back();

    while(!set.empty())
    {
        tNode = set.back(); set.pop_back();
        if(tNode != hNode1 && tNode != hNode2) 
        {
            tmp.push_back(tNode);
            count++;
            if(count == 2) break;
        }
    }

    while(!tmp.empty())
    {
        set.push_back(tmp.back()); tmp.pop_back();
    }
}

int* getTwoSmallestPercentageNodeIndexes(vector<HuffmanNode*>& set)
{
    int* smallest = new int[2];

    smallest[0] = 0;
    for(int i = 1; i < set.size(); i++)
    {
        if(set[i]->percentage <= set[smallest[0]]->percentage)
        {
            smallest[1] = smallest[0];
            smallest[0] = i;
        }
    }
    return smallest;
}

HuffmanNode* createHuffmanNode(double percentage, char* pString, HuffmanNode* left, HuffmanNode* right)
{
    HuffmanNode* hNode = new HuffmanNode;

    hNode->percentage = percentage;
    hNode->partitionStr = pString;
    hNode->left = left;
    hNode->right = right;

    return hNode;
}

codeWords codeWordsFromTree(HuffmanNode* root, int noOfCodeWords, bool firstCode)
{
    codeWords temp;
    //temp.resize(noOfCodeWords);
    codeWord codeWord;
    
    return cwFromTree(root, codeWord, temp, firstCode);
}

codeWords cwFromTree(HuffmanNode* node, codeWord& cW, codeWords& cWs, bool firstCode)
{
    if(node->left == NULL && node->right == NULL)
    {
        cWs.push_back(cW);
        for(int i = 0; i < cW.size(); i++)
        {
            cout << cW[i];
        }
        cout << endl;
    }
    else
    {
       codeWord cW2;
       for(int i = 0; i < cW.size(); i++)
       {   
            cW2.push_back(cW[i]);
       }

       cW.push_back(firstCode);
       cwFromTree(node->left, cW, cWs, firstCode);

       cW2.push_back(!firstCode);
       cwFromTree(node->right, cW2, cWs, firstCode);
    }
    return cWs;
}