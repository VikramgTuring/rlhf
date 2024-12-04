#if defined(__linux__)
#include <malloc.h>

void PrintMallocHistory() {
  fprintf(stderr, "Malloc history:\n");
  int size = malloc_history(0);
  for (int i = 0; i < size; i++) {
    const malloc_hist_entry* h = malloc_get_hist(0, i);
    fprintf(stderr, "%d bytes allocated at %.16s (%p)\n", h->size, h->alloc_site,
          h->addr);
  }
}

TEST(MyTest, LeakDetectionWithMallocHistory) {
  PrintMallocHistory();
  // Test code
  // Check if there's a memory leak by comparing malloc history
}

std::vector<my_hook_allocated>::trace_allocations_t tracked_allocations;


static void track_malloc(size_t size, void *ptr)

{

    ++my_hook_allocated::current_heap_size;

    tracked_allocations.emplace_back(ptrint(ptr), size);

}


static void track_free(void *ptr)

{

    if (my_hook_allocated::ptr_in_tracking(ptrint(ptr))) {

        --my_hook_allocated::current_heap_size;

        tracked_allocations.erase(std::remove_if(

                                        tracked_allocations.begin(),

                                        tracked_allocations.end(),

                                        std::bind(&my_hook_allocated::ptr_to_erase,

                                                ptrint(ptr))

                                ),

                            tracked_allocations.end());

    }

}


static void check_no_leaks()

{

    if (!my_hook_allocated::trace_allocations_t().empty()) {

        fprintf(stderr, "leaks!\n");

        for (const auto& t : my_hook_allocated::trace_allocations_t()) {

                auto r = std::make_unique<uint32_t>();

                if (t.m_ptr.load() == (/* some .... */)) {

                        ... leakage src matrix here.....

                }

        }

        abort();

    }

}

#endif  // defined(__linux__)
