#pragma once
template<typename T, typename Key, typename HashedKey, int size>
class FixedSizeHash
{
private:

    static const unsigned HASH_SIZE = size;
    T data[HASH_SIZE];
    Key key[HASH_SIZE];

public:
    void Init()
    {
        for (unsigned int i = 0; i < HASH_SIZE; ++i)
        {
            key[i] = -1;
        }
    }

    void Add(Key id, T& data)
    {
        HashedKey hashedId = id % HASH_SIZE;
        while(key[hashedId] >= 0)
        {
            hashedId = (hashedId + 1) % HASH_SIZE;
        }

        key[hashedId] = id;
        data[hashedId] = data;
    }

    HashedKey Find(Key id)
    {
        HashedKey hashedId = id % HASH_SIZE;
        auto currentKey = key[hashedId];

        while(currentKey != id)
        {
            if (currentKey == -1)
            {
                return -1;
            }

            hashedId = (hashedId + 1) % HASH_SIZE;
            currentKey = key[hashedId];
        }

        return hashedId;
    }

    void Remove(Key id)
    {
        auto hashedKey = Find(id);
        if (hashedKey != -1)
        {
            key[hashedKey] = -2;
        }
    }

    const T& Get(HashedKey hashedId)
    {
        return data[hashedId];
    }
};


template<typename T, typename Key, int size, typename HashedKey>
class HashBucket
{
private:
    static const unsigned BUCKET_SIZE = size;

public:
    struct Node
    {
        Node(const T& data_, const Key& key_) : key(key_), data(data_) {};
        T data;
        Key key;
        Node* next = nullptr;
        Node* previous = nullptr;
    };

    Node* buckets[BUCKET_SIZE];
public:
    void Init()
    {
        for(int i=0; i < BUCKET_SIZE; ++i)
        {
            buckets[i] = nullptr;
        }
    }

    void Add(const T& data, const Key& key)
    {
        HashedKey hashedKey = key % BUCKET_SIZE;
        if (buckets[hashedKey] == nullptr)
        {
            buckets[hashedKey] = new Node(data, key);
        }
        else
        {
            Node* n = new Node(data, key);
            n->next = buckets[hashedKey];
            buckets[hashedKey]->previous = n;
            buckets[hashedKey] = n;
        }
    }

    const T* Find(const Key& key)
    {
        HashedKey hashedKey = key % BUCKET_SIZE;
        Node* current = buckets[hashedKey];
        while(current != nullptr)
        {
            if (current->key == key)
            {
                return &current->data;
            }

            current = current->next;
        }

        return nullptr;
    }

    void Remove(Key key)
    {
        HashedKey hashedKey = key % BUCKET_SIZE;

        Node* current = buckets[hashedKey];
        while(current != nullptr)
        {
            if (current->key == key)
            {
                if (current == buckets[hashedKey])
                {
                    buckets[hashedKey] = buckets[hashedKey]->next;
                }
                else
                {
                    if(current->next)
                    {
                        current->next->previous = current->previous;
                    }

                    if (current->previous)
                    {
                        current->previous->next = current->next;
                    }
                }
                break;
            }
            else
            {
                current = current->next;
            }
        }
    }
};


