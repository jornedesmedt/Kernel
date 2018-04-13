#include <kernel/page_frame_allocator.h>

page_directory_t* kernel_directory;
page_directory_t* current_directory; //Directory for whatever task is currently running

uint32_t number_of_frames; //Number of frames that can be loaded