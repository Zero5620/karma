#include "modules/core/thread_pool.h"

#include "scene.h"

#ifndef KARMA_BUILD_TYPE
#define KARMA_BUILD_TYPE 0
#endif

int karma_client() {
#ifdef INIT_THREAD_POOL
	if (!async_initialize(2, mega_bytes(32), context.allocator)) {
		system_fatal_error("Thread could not be created");
	}
#endif
    
	#if (KARMA_BUILD_TYPE == 1)
	auto run = Scene_Run_Method_CLIENT;
	#else
	auto run = Scene_Run_Method_DEVELOP;
	#endif

	scene_prepare(run, Render_Backend_DIRECTX11, System_Window_Show_NORMAL);
    
	Scene* scene = scene_create();
    
	scene_load_resources();
    
	bool loaded = scene_load_level(scene, "rokkenjima");
	assert(loaded);
    
	scene_loop(scene);
    
	while (scene_running()) {
		scene_frame_begin(scene);
        
		scene_frame_simulate(scene);
        
		scene_begin_drawing();
        
		scene_render(scene);
        
		scene_end_drawing();
        
		scene_frame_end(scene);
	}
    
	scene_destroy(scene);
    
	scene_shutdown();
    
	return 0;
}