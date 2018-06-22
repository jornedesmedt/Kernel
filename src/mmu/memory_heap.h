namespace memory
{
    struct memory_node
    {
        size_t size;
        uintptr_t virtual_address;
        inline uintptr_t next_address() { return virtual_address + size; }
    } __attribute__((packed)) memory_node_t

    class memory_heap
    {
        public:
            inline bool has_parent(uint32_t index){ return index > 0; }
            inline bool has_children(uint32_t index){ return left(index) < m_size; }
            inline uint32_t parent(uint32_t index){ return (index-1) / 2 }
            inline uint32_t left(uint32_t index){ return 2 * index + 1; }
            inline uint32_t right(uint32_t index){ return 2 * index + 2; }

            void* malloc(size_t size);
            void* valloc(size_t size); //Align with pagesize
            void free(void *ptr);
        private:
            memory_node_t* m_free_nodes; //Heap for free nodes, sorted by size can be merged or split, starts with a single node covering the entire heap
            memory_node_t* m_allocated_nodes; //Heap for allocated nodes, sort by address, no merging or splitting allowed, starts empty
            uint32_t m_size; //The number of nodes in the heap
            uint32_t m_max_size; //The maximum number of nodes in the heap
    }
}