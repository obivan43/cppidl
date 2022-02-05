#pragma once

#include <utility>

template <typename C, typename P, typename... Args>
typename C::value_type FirstOrNull(const C& vec, P predicate, Args&&... args) {
	for (auto* element : vec)
		if (predicate(element, std::forward<Args>(args)...))
			return element;
	return nullptr;
}
