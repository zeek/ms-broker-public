#pragma once

#include <caf/meta/type_name.hpp>
#include <caf/node_id.hpp>

#include <vector>

#include "broker/convert.hh"
#include "broker/fwd.hh"
#include "broker/network_info.hh"
#include "broker/optional.hh"

namespace broker {

/// Information about an endpoint.
/// @relates endpoint
struct endpoint_info {
  endpoint_id node;               ///< A unique context ID per machine/process.
  optional<network_info> network; ///< Optional network-level information.
};

/// @relates endpoint_info
inline bool operator==(const endpoint_info& x, const endpoint_info& y) {
  return x.node == y.node && x.network == y.network;
}

/// @relates endpoint_info
inline bool operator!=(const endpoint_info& x, const endpoint_info& y) {
  return !(x == y);
}

/// @relates endpoint_info
template <class Inspector>
typename Inspector::result_type inspect(Inspector& f, endpoint_info& x) {
  if constexpr (detail::is_legacy_inspector<Inspector>)
    return f(caf::meta::type_name("endpoint_info"), x.node, x.network);
  else
    return f.object(x)
      .pretty_name("endpoint_info")
      .fields(f.field("node", x.node), f.field("network", x.network));
}

/// @relates endpoint_info
bool convertible_to_endpoint_info(const data& src);

/// @relates endpoint_info
bool convertible_to_endpoint_info(const std::vector<data>& src);

/// @relates endpoint_info
bool convert(const data& src, endpoint_info& dst);

/// @relates endpoint_info
bool convert(const endpoint_info& src, data& dst);

/// @relates endpoint_info
std::string to_string(const endpoint_info& x);

// Enable `can_convert` for `endpoint_info`.
template <>
struct can_convert_predicate<endpoint_info> {
  static bool check(const data& src) {
    return convertible_to_endpoint_info(src);
  }

  static bool check(const std::vector<data>& src) {
    return convertible_to_endpoint_info(src);
  }
};

} // namespace broker
