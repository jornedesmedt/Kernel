namespace memory
{
    class HeapAllocator
    {
        public:
            virtual ptr_t get_Heap_Start() = 0;
            virtual ptr_t get_Heap_End() = 0;
            virtual ptr_t set_Heap_start() = 0;
            virtual ptr_t set_Heap_End() = 0;
            virtual void* allocate(size_t size, ptr_t align = 0) = 0;
    }
}