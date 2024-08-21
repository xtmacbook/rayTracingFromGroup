#define SDL_MAIN_HANDLED

#include "../World/World.hpp"
#include "../Utilities/Debug.hpp"
#include "../Cameras/Camera.hpp"

int main(){
    World w;
    w.build();
    debug_print("Build finished.\n");
    if(w.tracer_ptr == nullptr){
        printf("Tracer nullptr. Aborting.\n");
        return 1;
    }
    if(w.camera == nullptr){
        printf("Camera nullptr. Aborting.\n");
        return 1;
    }
    w.camera->render_scene(w);
    printf("Main thread terminated.\n");
    return 0;
}