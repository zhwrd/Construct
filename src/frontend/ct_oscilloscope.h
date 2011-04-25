#ifndef SRC_FRONTEND_CT_OSCILLOSCOPE
#define SRC_FRONTEND_CT_OSCILLOSCOPE

#include <frontend/ct_widget.h>
#include <core/unit_generator.h>

namespace construct {
namespace frontend {

class CtOscilloscope : public CtWidget {
 public:
  CtOscilloscope(CtWidget* parent = NULL);
  virtual ~CtOscilloscope();

  virtual void Draw();

  inline core::UnitGenerator* unitgenerator() const {
    return unitgenerator_;
  }
  void set_unitgenerator(core::UnitGenerator* unitgenerator);

 private:
  core::UnitGenerator* unitgenerator_;
  int y_sample_;

};

} // namespace frontend
} // namespace construct

#endif
