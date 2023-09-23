#include "raylib.h"

struct AnimData
{
  Rectangle rec;
  Vector2 pos;
  int frame;
  float updateTime;
  float runningTime;
};

int main()
{
  // window dimensions
  int windowDimensions[2];
  windowDimensions[0] = 800;
  windowDimensions[1] = 600;
  const int frameRate{60};
  const char *title = "Dapper Dasher";
  const char *scarfyTexturePath = "textures/scarfy.png";
  const char *nebulaTexturePath = "textures/12_nebula_spritesheet.png";

  InitWindow(windowDimensions[0], windowDimensions[1], title);

  // acceleration due to gravity (pixels/second)/second
  const int gravity{1'000};
  // jump velocity (pixels/second)
  const int jumpVelocity{-600};

  // load the scarfy texture
  Texture2D scarfy = LoadTexture(scarfyTexturePath);
  AnimData scarfyData;
  scarfyData.rec.width = scarfy.width / 6;
  scarfyData.rec.height = scarfy.height;
  scarfyData.rec.x = 0;
  scarfyData.rec.y = 0;
  scarfyData.pos.x = windowDimensions[0] / 2 - scarfyData.rec.width / 2;
  scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
  scarfyData.frame = 0;
  scarfyData.updateTime = 1.0 / 12.0;
  scarfyData.runningTime = 0.0;

  // load the nebula texture
  Texture2D nebula = LoadTexture(nebulaTexturePath);

  // AnimData for nebula
  AnimData nebulaData{
      {0.0, 0.0, nebula.width / 8, nebula.height / 8},                // Rectangle rec
      {windowDimensions[0], windowDimensions[1] - nebula.height / 8}, // Vector2 pos
      0,                                                              // int frame
      1.0 / 12.0,                                                     // float updateTime
      0.0                                                             // float runningTime
  };

  AnimData nebula2Data{
      {0.0, 0.0, nebula.width / 8, nebula.height / 8},                      // Rectangle rec
      {windowDimensions[0] + 300, windowDimensions[1] - nebula.height / 8}, // Vector2 pos
      0,                                                                    // int frame
      1.0 / 16.0,                                                           // float updateTime
      0.0                                                                   // float runningTime
  };

  // nebula velocity (pixels/second)
  int nebulaVelocity{-200};

  // scarfy velocity (pixels/second)
  int velocity{0}; // pixels/frame
  bool isInAir{};  // is scarfy mid-jump?

  SetTargetFPS(frameRate);
  while (!WindowShouldClose())
  {
    // delta time (time since last frame)
    const float dT = GetFrameTime();

    // start drawing
    BeginDrawing();
    ClearBackground(WHITE);

    // check if rectangle is on the ground
    if (scarfyData.pos.y >= (windowDimensions[1] - scarfy.height))
    {
      // rectangle is on the ground
      velocity = 0;
      isInAir = false;
    }
    else
    {
      // apply gravity
      velocity += gravity * dT;
      isInAir = true;
    }

    // check for jumping
    if (IsKeyPressed(KEY_SPACE) && !isInAir)
    {
      velocity += jumpVelocity;
    }

    // update nebula position
    nebulaData.pos.x += nebulaVelocity * dT;
    nebula2Data.pos.x += nebulaVelocity * dT;

    // update scarfy position
    scarfyData.pos.y += velocity * dT;

    if (!isInAir)
    {
      // update running time
      scarfyData.runningTime += dT;
      if (scarfyData.runningTime >= scarfyData.updateTime)
      {
        scarfyData.runningTime = 0;
        // update animation frame
        scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
        scarfyData.frame++;
        if (scarfyData.frame > 5)
        {
          scarfyData.frame = 0;
        }
      }
    }

    // update nebula running time
    nebulaData.runningTime += dT;
    if (nebulaData.runningTime >= nebulaData.updateTime)
    {
      nebulaData.runningTime = 0;
      // update animation frame
      nebulaData.rec.x = nebulaData.frame * nebulaData.rec.width;
      nebulaData.frame++;
      if (nebulaData.frame > 7)
      {
        nebulaData.frame = 0;
      }
    }

    // update nebula running time
    nebula2Data.runningTime += dT;
    if (nebula2Data.runningTime >= nebula2Data.updateTime)
    {
      nebula2Data.runningTime = 0;
      // update animation frame
      nebula2Data.rec.x = nebula2Data.frame * nebula2Data.rec.width;
      nebula2Data.frame++;
      if (nebula2Data.frame > 7)
      {
        nebula2Data.frame = 0;
      }
    }

    // draw nebula
    DrawTextureRec(nebula, nebulaData.rec, nebulaData.pos, WHITE);
    DrawTextureRec(nebula, nebula2Data.rec, nebula2Data.pos, RED);

    // draw scarfy
    DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

    EndDrawing();

    if (nebulaData.pos.x <= (0 - nebula.width / 8))
    {
      nebulaData.pos.x = windowDimensions[0];
    }
    if (nebula2Data.pos.x <= (0 - nebula.width / 8))
    {
      nebula2Data.pos.x = windowDimensions[0];
    }
  }

  UnloadTexture(scarfy);
  UnloadTexture(nebula);
  CloseWindow();
}
