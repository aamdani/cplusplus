#include "raylib.h"
#include <iostream>

int main()
{
  // window dimensions and properties
  int width = 1280;
  int height = 1024;
  const char *title = "Axes & Allies: The Final World War!\n";
  const char *gameOver = "Game Over!\n";
  InitWindow(width, height, title);

  // circle coordinates
  int circle_x{width / 2};
  int circle_y{height / 2};
  int circle_radius{25};
  // circle edges
  int l_circle_x{circle_x - circle_radius};
  int r_circle_x{circle_x + circle_radius};
  int u_circle_y{circle_y - circle_radius};
  int b_circle_y{circle_y + circle_radius};

  // axe coordinates
  int axe_x{width / 2};
  int axe_y{0};
  int axe_length{50};
  // axe edges
  int l_axe_x{axe_x};
  int r_axe_x{axe_x + axe_length};
  int u_axe_y{axe_y};
  int b_axe_y{axe_y + axe_length};

  int direction{10};
  bool collision_with_axe =
      (b_axe_y >= u_circle_y) &&
      (u_axe_y <= b_circle_y) &&
      (r_axe_x >= l_circle_x) &&
      (l_axe_x <= r_circle_x);

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);

    // Game logic begins
    if (collision_with_axe)
    {
      DrawText(gameOver, width / 2, height / 2, 20, RED);
    }
    else
    {
      // update the edges
      l_circle_x = circle_x - circle_radius;
      r_circle_x = circle_x + circle_radius;
      u_circle_y = circle_y - circle_radius;
      b_circle_y = circle_y + circle_radius;
      l_axe_x = axe_x;
      r_axe_x = axe_x + axe_length;
      u_axe_y = axe_y;
      b_axe_y = axe_y + axe_length;
      // update collision_with_axe
      collision_with_axe =
          (b_axe_y >= u_circle_y) &&
          (u_axe_y <= b_circle_y) &&
          (r_axe_x >= l_circle_x) &&
          (l_axe_x <= r_circle_x);

      DrawCircle(circle_x, circle_y, circle_radius, RED);
      DrawRectangle(axe_x, axe_y, axe_length, axe_length, RED);

      // move the axe
      axe_y += direction;
      if (axe_y > (height - axe_length) || axe_y <= 0)
      {
        direction = -direction;
      }

      if (IsKeyDown(KEY_D) && (circle_x < (width - circle_radius)))
      {
        circle_x += 10;
      }

      if (IsKeyDown(KEY_A) && (circle_x > circle_radius))
      {
        circle_x -= 10;
      }

      if (IsKeyDown(KEY_W) && (circle_y > circle_radius))
      {
        circle_y -= 10;
      }

      if (IsKeyDown(KEY_S) && (circle_y < (height - circle_radius)))
      {
        circle_y += 10;
      }
    }

    // Game logic ends
    EndDrawing();
  }
}
