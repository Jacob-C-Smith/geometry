#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <json/json.h>
#include <geometry/geometry.h>

#include <SDL2/SDL.h>

enum color_e
{
    BLACK         = 0,
    BLUE          = 1,
    GREEN         = 2,
    CYAN          = 3,
    RED           = 4,
    MAGENTA       = 5,
    BROWN         = 6,
    LIGHT_GREY    = 7,
    DARK_GREY     = 8,
    LIGHT_BLUE    = 9,
    LIGHT_GREEN   = 10,
    LIGHT_CYAN    = 11,
    LIGHT_RED     = 12,
    LIGHT_MAGENTA = 13,
    LIGHT_BROWN   = 14,
    WHITE         = 15,
};
enum geometry_example_polygons
{
    GEOMETRY_POLYGON_CONVEX     = 0,
    GEOMETRY_POLYGON_CONCAVE    = 1,
    GEOMETRY_POLYGON_MOUNTAIN   = 2,
    GEOMETRY_POLYGON_MAZE       = 3,
    GEOMETRY_POLYGON_STAR       = 4, 
    GEOMETRY_POLYGON_GOALKEEPER = 5,
    GEOMETRY_POLYGON_FISH       = 6,
    GEOMETRY_POLYGON_QUANTITY   = 7,
};
char _convex_json[]     = "[{\"x\":150,\"y\":330},{\"x\":550,\"y\":330},{\"x\":700,\"y\":200},{\"x\":550,\"y\":50},{\"x\":150,\"y\":50}]",
     _concave_json[]    = "[{\"x\":150,\"y\":330},{\"x\":250,\"y\":250},{\"x\":550,\"y\":330},{\"x\":700,\"y\":200},{\"x\":550,\"y\":50},{\"x\":150,\"y\":50}]",
     _mountain_json[]   = "[{\"x\":150,\"y\":330},{\"x\":750,\"y\":330},{\"x\":650,\"y\":50},{\"x\":550,\"y\":300},{\"x\":450,\"y\":50},{\"x\":350,\"y\":300},{\"x\":250,\"y\":50}]",
     _maze_json[]       = "[{\"x\":120,\"y\":320},{\"x\":400,\"y\":320},{\"x\":400,\"y\":40},{\"x\":120,\"y\":40},{\"x\":120,\"y\":240},{\"x\":320,\"y\":240},{\"x\":320,\"y\":120},{\"x\":200,\"y\":120},{\"x\":200,\"y\":160},{\"x\":280,\"y\":160},{\"x\":280,\"y\":200},{\"x\":160,\"y\":200},{\"x\":160,\"y\":80},{\"x\":360,\"y\":80},{\"x\":360,\"y\":280},{\"x\":120,\"y\":280}]",
     _star_json[]       = "[{\"x\":80,\"y\":280},{\"x\":180,\"y\":200},{\"x\":320,\"y\":320},{\"x\":220,\"y\":180},{\"x\":400,\"y\":200},{\"x\":200,\"y\":140},{\"x\":240,\"y\":40},{\"x\":160,\"y\":120},{\"x\":80,\"y\":40},{\"x\":140,\"y\":180}]",
     _goalkeeper_json[] = "[{\"x\":80,\"y\":280},{\"x\":400,\"y\":320},{\"x\":700,\"y\":340},{\"x\":860,\"y\":320},{\"x\":820,\"y\":280},{\"x\":680,\"y\":300},{\"x\":680,\"y\":180},{\"x\":840,\"y\":140},{\"x\":820,\"y\":60},{\"x\":780,\"y\":80},{\"x\":800,\"y\":120},{\"x\":640,\"y\":140},{\"x\":580,\"y\":180},{\"x\":520,\"y\":180},{\"x\":480,\"y\":60},{\"x\":400,\"y\":20},{\"x\":240,\"y\":40},{\"x\":260,\"y\":80},{\"x\":420,\"y\":60},{\"x\":380,\"y\":200},{\"x\":300,\"y\":100},{\"x\":220,\"y\":120},{\"x\":240,\"y\":180},{\"x\":320,\"y\":220},{\"x\":280,\"y\":260},{\"x\":220,\"y\":260},{\"x\":100,\"y\":240}]",
     _fish_json[]       = "[{\"x\":180,\"y\":180},{\"x\":240,\"y\":220},{\"x\":320,\"y\":220},{\"x\":380,\"y\":200},{\"x\":440,\"y\":160},{\"x\":480,\"y\":180},{\"x\":520,\"y\":240},{\"x\":520,\"y\":20},{\"x\":480,\"y\":80},{\"x\":440,\"y\":100},{\"x\":400,\"y\":40},{\"x\":340,\"y\":20},{\"x\":300,\"y\":20},{\"x\":260,\"y\":40},{\"x\":200,\"y\":60},{\"x\":180,\"y\":80},{\"x\":140,\"y\":140}]";
char *_p_polygon_data[GEOMETRY_POLYGON_QUANTITY] =
    {
        _convex_json,
        _concave_json,
        _mountain_json,
        _maze_json,
        _star_json,
        _goalkeeper_json,
        _fish_json
    };
unsigned long _colors [16] =
{
    0x000000,
    0x0000AA,
    0x00AA00,
    0x00AAAA,
    0xAA0000,
    0xAA00AA,
    0xAA5500,
    0xAAAAAA,
    0x555555,
    0x5555FF,
    0x55FF55,
    0x55FFFF,
    0xFF5555,
    0xFF55FF,
    0xFFFF55,
    0xFFFFFF,
};

int draw_geometry ( geometry *p_geometry, SDL_Renderer *p_renderer, enum color_e color, int x, int y, float scale )
{
    
    unsigned long c = _colors[color];

    SDL_SetRenderDrawColor(
        p_renderer,
        (c & 0xff0000) >> 16,
        (c & 0x00ff00) >> 8,
        (c & 0x0000ff),
        255
    );

    for (size_t i = 1; i < p_geometry->polygon.quantity; i++)
    {
        SDL_RenderDrawLine(
            p_renderer,
            p_geometry->polygon.p_verticies[i-1].x * scale + x,
            p_geometry->polygon.p_verticies[i-1].y * scale + y,
            p_geometry->polygon.p_verticies[i].x * scale + x,
            p_geometry->polygon.p_verticies[i].y * scale + y
        );
    }
    
    SDL_RenderDrawLine(
        p_renderer,
        p_geometry->polygon.p_verticies[0].x * scale + x,
        p_geometry->polygon.p_verticies[0].y * scale + y,
        p_geometry->polygon.p_verticies[p_geometry->polygon.quantity-1].x * scale + x,
        p_geometry->polygon.p_verticies[p_geometry->polygon.quantity-1].y * scale + y
    );

    return 1;
}

int main ( int argc, const char *argv[] )
{

    SDL_Window *window = SDL_CreateWindow("Geometry rasterizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 550, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Event e;
    bool running = true;
    char *_convex_json = _p_polygon_data[GEOMETRY_POLYGON_MAZE];
    char *_convex_json2 = _p_polygon_data[GEOMETRY_POLYGON_FISH];
    json_value *p_value = (void *) 0;
    json_value *p_value2 = (void *) 0;
    geometry _geometry = { 0 };
    geometry _geometry2 = { 0 };
    geometry _geometry3 = { 0 };

    // Parse the goalkeeper json text into a value
    if ( json_value_parse(_convex_json, 0, &p_value) == 0 ) goto failed_to_parse_json;

    // Construct the simple geometry
    if ( geometry_polygon_load_as_json(&_geometry, p_value) == 0 ) goto failed_to_construct_polygon;

    // Parse the goalkeeper json text into a value
    if ( json_value_parse(_convex_json2, 0, &p_value2) == 0 ) goto failed_to_parse_json;

    // Construct the simple geometry
    if ( geometry_polygon_load_as_json(&_geometry2, p_value2) == 0 ) goto failed_to_construct_polygon;

    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            
            default:
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        SDL_RenderClear(renderer);

        draw_geometry(&_geometry , renderer, RED  , 0, 0  , 0.5);
        draw_geometry(&_geometry2, renderer, GREEN, 0, 180, 0.5);
        draw_geometry(&_geometry3, renderer, BLUE , 0, 360, 0.5);

        SDL_RenderPresent(renderer);
    }
    
    failed_to_parse_json:
    failed_to_construct_polygon:

    // Success
    return EXIT_SUCCESS;
}
