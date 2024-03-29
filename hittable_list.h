#pragma once
#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <memory>
#include <vector>
#include "hittable.h"
#include "ray.h"

class hittable_list : public hittable{
public:
	std::vector<std::shared_ptr<hittable>> objects;

	hittable_list(){}
	hittable_list(std::shared_ptr<hittable> object) { add(object);	}
	
	void add(std::shared_ptr<hittable> object) {
		objects.push_back(object);
	}

	bool hit(const ray& r, double ray_tmin, double ray_tmax, hitInfo& rec) const override {
		hitInfo temp_rec;
		bool hit_anything = false;
		auto closest_so_far = ray_tmax;

		for (const auto& object : objects) {
			if (object->hit(r, ray_tmin, closest_so_far, temp_rec)) {
				hit_anything = true;
				closest_so_far = temp_rec.t;
				rec = temp_rec;
			}
		}

		return hit_anything;
	}
};

#endif // !HITTABLE_LIST_H
