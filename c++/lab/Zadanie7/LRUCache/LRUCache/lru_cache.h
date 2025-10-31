// LRUCache.h
#ifndef LRUCACHE_H
#define LRUCACHE_H

#include "hash_table.h"
#include "listTwo.h"
#include <string>

class LRUCache {
private:
    int capacity;
    ForwardListTwo usageList;
    ChainingHashTable* cacheMap;

    void moveToFront(int key) {
        string keyStr = to_string(key);
        DoublyNode* current = usageList.head;
        while (current != nullptr) {
            if (current->node.find(keyStr + ":") == 0) {
                string nodeData = current->node;
                deleteNodeIndexTwo(&usageList, nodeData);
                addNodeHeadTwo(&usageList, nodeData);
                break;
            }
            current = current->next;
        }
    }

    void removeLRU() {
        if (usageList.tail != nullptr) {
            string lruData = usageList.tail->node;
            size_t colonPos = lruData.find(':');
            if (colonPos != std::string::npos) {
                int key = stoi(lruData.substr(0, colonPos));
                cacheMap->remove(key);
            }
            deleteNodeTailTwo(&usageList);
        }
    }

public:
    LRUCache(int cap) : capacity(cap) {
        usageList.head = nullptr;
        usageList.tail = nullptr;
        cacheMap = new ChainingHashTable(100);
    }

    ~LRUCache() {
        while (usageList.head != nullptr) {
            deleteNodeHeadTwo(&usageList);
        }
        delete cacheMap;
    }

    void set(int key, int value) {
        string keyStr = to_string(key);
        string itemStr = keyStr + ":" + to_string(value);

        if (cacheMap->search(key)) {
            moveToFront(key);
            DoublyNode* current = usageList.head;
            while (current != nullptr) {
                if (current->node.find(keyStr + ":") == 0) {
                    current->node = itemStr;
                    break;
                }
                current = current->next;
            }
        }
        else {
            if (countNodesTwo(usageList) >= capacity) {
                removeLRU();
            }
            cacheMap->insert(key);
            addNodeHeadTwo(&usageList, itemStr);
        }
    }

    int get(int key) {
        if (cacheMap->search(key)) {
            moveToFront(key);
            string keyStr = to_string(key);
            DoublyNode* current = usageList.head;
            while (current != nullptr) {
                if (current->node.find(keyStr + ":") == 0) {
                    size_t colonPos = current->node.find(':');
                    if (colonPos != std::string::npos) {
                        return stoi(current->node.substr(colonPos + 1));
                    }
                }
                current = current->next;
            }
        }
        return -1;
    }

    void printCache() {
        cout << "LRU Cache: ";
        DoublyNode* current = usageList.head;
        while (current != nullptr) {
            cout << "[" << current->node << "] ";
            current = current->next;
        }
        cout << endl;
    }
};

void processLRUQueries();

#endif