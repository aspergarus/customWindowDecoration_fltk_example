#include <FL/Fl.H>
#include <FL/Enumerations.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Double_Window.H>

#include <Fl/Fl_Box.H>
#include <FL/Fl_Button.H>

#include <FL/Fl_Image.H>
#include <FL/Fl_Tiled_Image.H>
#include <FL/Fl_PNG_Image.H>

#include <iostream>

const int WIDTH = 666;
const int HEIGHT = 510;
const int topW = 558, topH = 22;
const int bottomW = 558, bottomH = 22;
const int leftW = 24, leftH = 396;
const int rightW = 24, rightH = 396;

const int topLeftW = 53, topLeftH = 57;
const int bottomLeftW = 53, bottomLeftH = 57;
const int topRightW = 54, topRightH = 57;
const int bottomRightW = 54, bottomRightH = 57;

class MovableBox: public Fl_Box {
    Fl_Window *currentWindow;

    public:
        MovableBox(int x, int y, int w, int h, const char* title = nullptr): Fl_Box(x, y, w, h, title) {}

        void setWindow(Fl_Window *win) {
            this->currentWindow = win;
        }

        int handle(int event) {
            std::cout << "Event in MovableBox:" << event << "\n";
            static int xs = 0, ys = 0, winx = 0, winy = 0;

            if (event == FL_PUSH) {
                xs = Fl::event_x_root();
                ys = Fl::event_y_root();
                winx = window()->x_root();
                winy = window()->y_root();
                return 1;
            } else if (event == FL_DRAG) {
                int dx = Fl::event_x_root() - xs;
                int dy = Fl::event_y_root() - ys;
                this->currentWindow->position(winx + dx, winy + dy);
            }

            if (event == FL_Enter) {
                std::cout << "Event in MovableBox: FL_Enter: " << event << "\n";
                this->currentWindow->cursor(FL_CURSOR_MOVE);
            }

            if (event == FL_LEAVE) {
                this->currentWindow->cursor(FL_CURSOR_ARROW);
            }

            return Fl_Box::handle(event);
        }
};

void borderHide(Fl_Widget* w, void* p){
    Fl_Window* win = (Fl_Window*) p;
    win->border(0);
}

void borderShow(Fl_Widget* w, void* p){
    Fl_Window* win = (Fl_Window*) p;
    win->border(1);
}

int main() {
    Fl_Double_Window *win = new Fl_Double_Window(WIDTH - 1, HEIGHT, "Starcraft-like window");

    {
        Fl_Image *image = new Fl_PNG_Image("./starcraft/content.png");
        auto contentBox = new Fl_Box(12, 11, WIDTH - rightW, HEIGHT - bottomH);
        // contentBox->color(FL_WHITE);
        // contentBox->align(FL_ALIGN_CENTER);
        contentBox->image(image);
        // Fl_Group::current()->resizable(contentBox);
        // win->resizable(contentBox);
    }

    // Movable top border
    {
        Fl_Image *image = new Fl_PNG_Image("./starcraft/top.png");
        auto bar = new MovableBox(topLeftW, 0, topW, topH);
        bar->setWindow(win);
        bar->box(FL_FLAT_BOX);
        bar->labelsize(18);
        bar->labelcolor(FL_WHITE);
        bar->color(FL_DARK_MAGENTA);
        bar->image(image);
    }

    // Top Left Corner
    {
        Fl_Image *image = new Fl_PNG_Image("./starcraft/top_left.png");
        auto border = new Fl_Box(0, 0, topLeftW, topLeftH);
        border->image(image);
    }

    // Left border
    {
        Fl_Image *image = new Fl_PNG_Image("./starcraft/left.png");
        auto border = new Fl_Box(0, topLeftH, leftW, leftH);
        border->image(image);
    }

    // Bottom Left Corner
    {
        Fl_Image *image = new Fl_PNG_Image("./starcraft/bottom_left.png");
        auto border = new Fl_Box(0, HEIGHT - bottomLeftH, bottomLeftW, bottomLeftH);
        border->image(image);
    }

    // Bottom border
    {
        Fl_Image *image = new Fl_PNG_Image("./starcraft/bottom.png");
        auto border = new Fl_Box(bottomLeftW, HEIGHT - bottomH, bottomW, bottomH);
        border->image(image);
    }

    // Bottom Right Corner
    {
        Fl_Image *image = new Fl_PNG_Image("./starcraft/bottom_right.png");
        auto border = new Fl_Box(WIDTH - bottomRightW - 1, HEIGHT - bottomRightH, bottomRightW, bottomRightH);
        border->image(image);
    }

    // Right border
    {
        Fl_Image *image = new Fl_PNG_Image("./starcraft/right.png");
        auto border = new Fl_Box(WIDTH - rightW, HEIGHT - rightH - bottomRightH, rightW, rightH);
        border->image(image);
    }

    // Top Right Corner
    {
        Fl_Image *image = new Fl_PNG_Image("./starcraft/top_right.png");
        auto border = new Fl_Box(WIDTH - topRightW - 1, 0, topRightW, topRightH);
        border->image(image);
    }
    

    // Hide the border from the first execution.
    // win->clear_border();
    win->border(0);

    // Button which implements the border() function for showing the border.
    Fl_Button* S = new Fl_Button(80,150,100,30,"Border on");
    S->callback(borderShow, win);


    // Button which implements the border() function for hiding the border.
    Fl_Button* H = new Fl_Button(80,100,100,30,"Border off");
    H->callback(borderHide, win);

    win->end();
    
    win->show();
   
    return Fl::run();

}
