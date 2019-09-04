#include "broker/defaults.hh"

#include <limits>

namespace broker {
namespace defaults {

const caf::string_view output_generator_file = "";

const size_t output_generator_file_cap = std::numeric_limits<size_t>::max();

} // namespace defaults
} // namespace broker
