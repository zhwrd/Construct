#ifndef SRC_FRONTEND_CT_OSCILLOSCOPE
#define SRC_FRONTEND_CT_OSCILLOSCOPE

#include "frontend/ct_widget.h"

namespace construct {
namespace core {
class UnitGenerator;
} // namespace core
namespace frontend {

class CtOscilloscope : public CtWidget {
 public:
  explicit CtOscilloscope(CtWidget* parent = NULL);
  virtual ~CtOscilloscope();

  virtual void Draw();

  inline core::UnitGenerator* unit_generator() const {
    return unit_generator_;
  }
  void set_unit_generator(core::UnitGenerator* unit_generator);

 private:
  core::UnitGenerator* unit_generator_;
  int y_sample_;

};

} // namespace frontend
} // namespace construct

#endif
