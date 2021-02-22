#include <unistd.h>
#include "LeaderboardRenderer.h"
#include "../common_src/GameConstants.h"

LeaderboardRenderer::LeaderboardRenderer(SDL_Renderer *renderer,
                                         TexturesContainer &tex,
                                         const std::string &font_path,
                                         int height, int width):
                                         tex(tex), height(height),
                                         width(width), renderer(renderer) {
    int title_font_size = height/15;
    int name_font_size = height/20;
    int value_font_size = height/24;
    SDL_Color title_color = {162, 31, 9};
    SDL_Color color = {240, 250, 252};

    titles.emplace_back(font_path, title_font_size, title_color, renderer, "Kills");
    titles.emplace_back(font_path, title_font_size, title_color, renderer, "Score");
    titles.emplace_back(font_path, title_font_size, title_color, renderer, "Bullets Fired");

    for(int i=0; i<LEADERBOARD_ELEMENTS; i++) {
        names.emplace_back(font_path, name_font_size, color, renderer, "0");
        values.emplace_back(font_path, value_font_size, color, renderer, "0");
    }
}

void LeaderboardRenderer::render(std::vector<std::string> &names,
                                 std::vector<int> &values) {

    usleep(LEADERBOARD_SLEEP_TIME_1);

    tex.getStatic(LB_Back)->render(nullptr, nullptr);
    _render();

    int margin = width/32;
    int big_margin = margin + width/96;
    int column = (7*width)/24;
    int text_column = (9*width)/32;
    int thick_space = height/36;

    SDL_Rect kills = {big_margin, height/10, text_column, height/15};
    SDL_Rect score = {big_margin+margin+column, height/10, text_column, height/15};
    SDL_Rect fired = {big_margin+2*margin+2*column, height/10, text_column, height/15};
    _render();

    usleep(LEADERBOARD_SLEEP_TIME_2);

    titles[0].renderHorizontallyCentered("Kills", nullptr, &kills);
    titles[1].renderHorizontallyCentered("Score", nullptr, &score);
    titles[2].renderHorizontallyCentered("Bullets Fired", nullptr, &fired);
    _render();

    int accumulated = height/10 + height/15 + thick_space;
    int iterations = (LEADERBOARD_ELEMENTS/3)*2;
    int j = 0;

    for (int i=0; i<iterations; i++) {
        usleep(LEADERBOARD_SLEEP_TIME_2);

        int text_heigth = (i%2 == 0)? height/20: height/28;
        int space = (i%2 == 0)? 0: 2*thick_space;

        SDL_Rect kill_data = {big_margin, accumulated, text_column, text_heigth};
        SDL_Rect score_data = {big_margin+margin+column, accumulated,text_column, text_heigth};
        SDL_Rect fired_data = {big_margin+2*margin+2*column, accumulated,text_column, text_heigth};

        if (i%2 == 0) {
            this->names[j].renderHorizontallyCentered(names[j], nullptr, &kill_data);
            this->names[j+5].renderHorizontallyCentered(names[j+5], nullptr, &score_data);
            this->names[j+10].renderHorizontallyCentered(names[j+10], nullptr, &fired_data);
        } else {
            this->values[j].renderHorizontallyCentered(std::to_string(values[j]), nullptr, &kill_data);
            this->values[j+5].renderHorizontallyCentered(std::to_string(values[j+5]), nullptr, &score_data);
            this->values[j+10].renderHorizontallyCentered(std::to_string(values[j+10]), nullptr, &fired_data);
            j++;
        }
        accumulated += text_heigth + space;
        _render();
    }
}

LeaderboardRenderer::~LeaderboardRenderer() {}



void LeaderboardRenderer::_render() {
    SDL_RenderPresent(this->renderer);
}
