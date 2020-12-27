#ifndef GUIPROVIDER_H
#define GUIPROVIDER_H

namespace odo {

class GuiProvider {
public:
  virtual ~GuiProvider(){};

  /**
   * @brief Render the UI to the GUI frame.
   */
  virtual void render_ui() = 0;
};
} // namespace odo

#endif // GUIPROVIDER_H
