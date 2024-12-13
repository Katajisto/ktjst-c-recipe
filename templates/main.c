#include <SDL3/SDL.h>
#include <SDL3/SDL_gpu.h>
#include <complex.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
  /* init SDL and renderer */
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Init(SDL_INIT_EVENTS);  
  SDL_Window* window = SDL_CreateWindow("window", 500, 500, SDL_WINDOW_OPENGL);

  SDL_GPUDevice* device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV, true, NULL);
  SDL_ClaimWindowForGPUDevice(device, window);
  
  SDL_GPUCommandBuffer* cmdbuf = SDL_AcquireGPUCommandBuffer(device);
  
  /* main loop */
  for (;;) {
    /* handle SDL events */
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
        case SDL_EVENT_QUIT: exit(EXIT_SUCCESS); break;
      }
    }

    SDL_BeginGPURenderPass(cmdbuf)
    
  }

  return 0;
}

