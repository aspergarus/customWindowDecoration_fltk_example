#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>

#include <cstdio>
#include <functional>

#define WIDTH 600
#define HEIGHT 400
#define BLUE fl_rgb_color(0x42, 0xA5, 0xF5)
#define SEL_BLUE fl_rgb_color(0x21, 0x96, 0xF3)
#define GRAY fl_rgb_color(0x75, 0x75, 0x75)
#define LIGHT_GRAY fl_rgb_color(211, 211, 211)

using cb_t = std::function<void(Fl_Widget *)>;

class MyBox : public Fl_Box {
  public:
    MyBox(int x, int y, int w, int h, const char *title = NULL): Fl_Box(x, y, w, h, title) {}
    virtual void draw() override {
        fl_rectf(0, h(), w(), 3, LIGHT_GRAY);
        Fl_Box::draw();
    }
};

template <typename T>
class WidgetWrapper : public T {
    cb_t func_ = NULL;

  public:
    WidgetWrapper(int x, int y, int w, int h, const char *title = NULL): T(x, y, w, h, title) {}
    void set_cb(cb_t &&func) {
        func_ = func;
        auto cb = [](Fl_Widget *w, void *data) {
            auto fn = *static_cast<cb_t *>(data);
            fn(w);
        };
        this->callback(cb, &func_);
    }
};

int main() {
    auto win = new Fl_Window(WIDTH, HEIGHT, "Flutter-like");
    auto bar = new WidgetWrapper<MyBox>(0, 0, WIDTH, 60, "    FLTK APP");
    bar->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    auto txt = new WidgetWrapper<Fl_Box>(
        250, 180, 100, 40, "You have pushed the button this many times:");
    auto count = new WidgetWrapper<Fl_Box>(txt->x(), txt->y() + 40, 100, 40, "0");
    auto but = new WidgetWrapper<Fl_Button>(WIDTH - 100, HEIGHT - 100, 60, 60, "@+6plus");
    win->end();
    win->show();

    // theming
    Fl::background(255, 255, 255);
    Fl::visible_focus(false);
    
    bar->box(FL_FLAT_BOX);
    bar->labelsize(22);
    bar->labelcolor(FL_WHITE);
    bar->color(BLUE);

    txt->labelsize(18);
    txt->labelfont(FL_TIMES);

    count->labelsize(36);
    count->labelcolor(GRAY);

    but->color(BLUE);
    but->selection_color(SEL_BLUE);
    but->labelcolor(FL_WHITE);
    but->box(FL_OFLAT_BOX);
    // end theming

    but->set_cb([=](Fl_Widget *b) {
        auto label = atoi(count->label());
        label += 1;
        char buf[12];
        (void)snprintf(buf, 12, "%d", label);
        count->copy_label(buf);
    });

    return Fl::run();
}
