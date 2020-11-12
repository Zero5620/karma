#include "scene.h"
#include <time.h>

#include "modules/core/systems.h"
#include ".generated/entity.typeinfo"

Scene *scene_create() {
	Scene *scene = new Scene;
	
	circular_linked_list_init(&scene->rigid_bodies, context.allocator);

	scene->pool_allocator = context.allocator;

	scene->id_series = random_init(context.id, system_get_counter());

	return scene;
}

void scene_destroy(Scene *scene) {
	// TODO: Distroy other objects as well
	memory_free(scene);
}

u64 iscene_generate_unique_id(Scene *scene) {
	u64 id = 0;
	while (id == 0) {
		id = (u64)random_get(&scene->id_series) | (((u64)time(0) & 0xffffffff) << 32);
	}
	return id;
}

Resource_Fixture *scene_find_resource_fixture(Scene *scene, Resource_Id id) {
	auto res = array_find(&scene->resource_fixtures, [](const Resource_Fixture &f, Resource_Id id) { return f.id == id; }, id);
	if (res >= 0) return scene->resource_fixtures.data + res;
	return nullptr;
}

Resource_Id scene_create_new_resource_fixture(Scene *scene, Fixture *fixtures, u32 fixture_count) {
	Resource_Fixture *resource = array_add(&scene->resource_fixtures);

	resource->id = iscene_generate_unique_id(scene);
	resource->fixture_count = fixture_count;
	resource->fixtures = new (scene->pool_allocator) Fixture[resource->fixture_count];

	Fixture *dst = resource->fixtures;
	Fixture *src;
	ptrsize size = 0;
	for (u32 index = 0; index < fixture_count; ++index) {
		src = fixtures + index;

		switch (src->shape) {
			case Fixture_Shape_Null:	invalid_code_path(); break;
			case Fixture_Shape_Circle:	size = sizeof(Circle); break;
			case Fixture_Shape_Mm_Rect: size = sizeof(Mm_Rect); break;
			case Fixture_Shape_Capsule: size = sizeof(Capsule); break;
			case Fixture_Shape_Polygon: size = sizeof(Polygon) + sizeof(Vec2) * ((Polygon *)src->handle)->vertex_count; break;

			invalid_default_case();
		}

		dst->shape = src->shape;
		dst->handle = memory_allocate(size, scene->pool_allocator);
		memcpy(dst->handle, src->handle, size);

		dst += 1;
	}

	return resource->id;
}

bool scene_delete_resource_fixture(Scene *scene, Resource_Id id) {
	auto index = array_find(&scene->resource_fixtures, [](const Resource_Fixture &r, Resource_Id id) { return r.id == id; }, id);
	if (index >= 0) {
		auto resource = &scene->resource_fixtures[index];
		for (u32 i = 0; i < resource->fixture_count; ++i)
			memory_free(resource->fixtures[i].handle);
		memory_free(resource->fixtures);
		array_remove(&scene->resource_fixtures, index);
		return true;
	}
	return false;
}

Camera *scene_add_camera(Scene *scene) {
	Camera *camera = array_add(&scene->by_type.camera);
	camera->type = Entity_Type_Camera;
	return camera;
}

Character *scene_add_character(Scene *scene) {
	Character *character = array_add(&scene->by_type.character);
	character->type = Entity_Type_Character;
	return character;
}

Obstacle *scene_add_obstacle(Scene *scene) {
	Obstacle *obstacle = array_add(&scene->by_type.obstacle);
	obstacle->type = Entity_Type_Obstacle;
	return obstacle;
}

Mm_Rect rigid_body_bounding_box(Rigid_Body *body, r32 dt) {
	Mm_Rect local_min_rect;
	local_min_rect.min = vec2( MAX_FLOAT);
	local_min_rect.max = vec2(-MAX_FLOAT);

	for (u32 index = 0; index < body->fixture_count; ++index) {
		Fixture *fixture = rigid_body_get_fixture(body, index);
		switch (fixture->shape) {
			case Fixture_Shape_Null: break;

			case Fixture_Shape_Circle: {
				auto circle = fixture_get_shape(fixture, Circle);
				auto rect = mm_rect_enclosing_circle(*circle);
				local_min_rect.min = vec2_min(local_min_rect.min, rect.min);
				local_min_rect.max = vec2_max(local_min_rect.max, rect.max);
			} break;

			case Fixture_Shape_Mm_Rect: {
				auto rect = fixture_get_shape(fixture, Mm_Rect);
				local_min_rect.min = vec2_min(local_min_rect.min, rect->min);
				local_min_rect.max = vec2_max(local_min_rect.max, rect->max);
			} break;

			case Fixture_Shape_Capsule: {
				auto capsule = fixture_get_shape(fixture, Capsule);
				auto rect = mm_rect_enclosing_capsule(*capsule);
				local_min_rect.min = vec2_min(local_min_rect.min, rect.min);
				local_min_rect.max = vec2_max(local_min_rect.max, rect.max);
			} break;

			case Fixture_Shape_Polygon: {
				auto polygon = fixture_get_shape(fixture, Polygon);
				auto rect = mm_rect_enclosing_polygon(*polygon);
				local_min_rect.min = vec2_min(local_min_rect.min, rect.min);
				local_min_rect.max = vec2_max(local_min_rect.max, rect.max);
			} break;

			invalid_default_case();
		} 
	}

	Vec2 dp = dt * body->velocity;

	local_min_rect.min = vec2_min(local_min_rect.min, local_min_rect.min + dp);
	local_min_rect.max = vec2_max(local_min_rect.max, local_min_rect.max + dp);

	Vec2 a, b, c, d;
	a = local_min_rect.min;
	b = vec2(local_min_rect.min.x, local_min_rect.max.y);
	c = local_min_rect.max;
	d = vec2(local_min_rect.max.x, local_min_rect.min.y);

	a = mat2_vec2_mul(body->transform.xform, a) + body->transform.p;
	b = mat2_vec2_mul(body->transform.xform, b) + body->transform.p;
	c = mat2_vec2_mul(body->transform.xform, c) + body->transform.p;
	d = mat2_vec2_mul(body->transform.xform, d) + body->transform.p;

	return mm_rect_enclosing_quad(a, b, c, d);
}

Rigid_Body *iscene_create_rigid_body(Scene *scene, Entity_Id entity_id, const Rigid_Body_Info *info) {
	auto node = circular_linked_list_add(&scene->rigid_bodies);
	Rigid_Body *rigid_body = &node->data;
	rigid_body->type = info->type;
	rigid_body->flags = 0;
	rigid_body->drag = 5;
	rigid_body->imass = (info->type == Rigid_Body_Type_Dynamic) ? 1.0f : 0.0f;
	rigid_body->velocity = vec2(0);
	rigid_body->force = vec2(0);
	rigid_body->transform = info->transform;
	rigid_body->restitution = 0;
	rigid_body->entity_id = entity_id;

	if (info->fixture_id) {
		Resource_Fixture *resource  = scene_find_resource_fixture(scene, info->fixture_id);
		rigid_body->fixtures		= resource->fixtures;
		rigid_body->fixture_count	= resource->fixture_count;
	} else {
		rigid_body->fixture_count	= 0;
		rigid_body->fixtures		= 0;
	}

	rigid_body->bounding_box = rigid_body_bounding_box(rigid_body, 0);

	return rigid_body;
}

void iscene_destroy_rigid_body(Scene *scene, Rigid_Body *rigid_body) {
	auto node = circular_linked_list_node_from_data(rigid_body);
	circular_linked_list_remove(&scene->rigid_bodies, node);
}

Entity *scene_create_new_entity(Scene *scene, Entity_Type type, const Entity_Info &info) {
	Entity *entity = nullptr;

	Entity_Id id = iscene_generate_unique_id(scene);

	switch (type) {
		case Entity_Type_Camera: {
			auto camera = (Camera *)scene_add_camera(scene);
			auto camera_info = (Camera_Info *)info.data;
			camera->distance = camera_info->distance;
			camera->target_position = camera_info->target_position;
			camera->target_distance = camera_info->target_distance;
			camera->follow_factor = camera_info->follow_factor;
			camera->zoom_factor = camera_info->zoom_factor;
			camera->behaviour = camera_info->behaviour;
			camera->lens = camera_info->lens;
			entity = camera;
		} break;

		case Entity_Type_Character: {
			auto player = (Character *)scene_add_character(scene);
			player->radius = 1;
			player->color = vec4(1);
			player->intensity = 1;
			player->rigid_body = iscene_create_rigid_body(scene, id, (Rigid_Body_Info *)info.data);
			entity = player;
		} break;

		case Entity_Type_Obstacle: {
			auto obstacle = (Obstacle *)scene_add_obstacle(scene);
			obstacle->color = vec4(1);
			obstacle->rigid_body = iscene_create_rigid_body(scene, id, (Rigid_Body_Info *)info.data);
			entity = obstacle;
		} break;
	}

	entity->type = type;
	entity->position = info.position;
	return entity;
}

//
//
//

#if 0

void serialize_collider(Scene *scene, Collider &collider, Ostream *out) {
	switch (collider.type) {
	case Collider_Null: {
		serialize_fmt_text(out, "collider_data", reflect_info<Null>(), (char *)collider.handle);
	} break;

	case Collider_Circle: {
		serialize_fmt_text(out, "collider_data", reflect_info<Circle>(), (char *)collider.handle);
	} break;

	case Collider_Mm_Rect: {
		serialize_fmt_text(out, "collider_data", reflect_info<Mm_Rect>(), (char *)collider.handle);
	} break;

	case Collider_Capsule: {
		serialize_fmt_text(out, "collider_data", reflect_info<Capsule>(), (char *)collider.handle);
	} break;

	case Collider_Polygon: {
		Polygon *polygon = collider_get_shape(&collider, Polygon);
		Array_View<Vec2> points;
		points.count = polygon->vertex_count;
		points.data = polygon->vertices;
		serialize_fmt_text(out, "collider_data", reflect_info(points), (char *)&points);
	} break;

		invalid_default_case();
	}
}

void serialize_collider_group(Scene *scene, Collider_Group &group, Ostream *out) {
	serialize_fmt_text(out, "collider_group_count", reflect_info(group.count), (char *)&group.count);

	for (u32 index = 0; index < group.count; ++index) {
		auto collider = collider_get(scene, collider_node(group.handle, index));
		serialize_fmt_text_next(out);
		serialize_fmt_text(out, "collider_type", reflect_info<Collider_Type>(), (char *)&collider->type);
		serialize_fmt_text_next(out);
		serialize_collider(scene, *collider, out);
	}
}

void serialize_entity(Scene *scene, Entity *entity, Ostream *out) {
	serialize_fmt_text(out, "type", reflect_info<Entity_Type>(), (char *)&entity->type);
	serialize_fmt_text_next(out);

	switch (entity->type) {
	case Entity_Player: {
		serialize_fmt_text(out, "player", reflect_info<Player>(), (char *)entity);
	} break;

	case Entity_Static_Body: {
		serialize_fmt_text(out, "static_body", reflect_info<Static_Body>(), (char *)entity);
		serialize_fmt_text_next(out);
		serialize_collider_group(scene, ((Static_Body *)entity)->colliders, out);
	} break;

		invalid_default_case();
	}

}

bool deserialize_collider(Scene *scene, Collider_Type type, Collider_Node *node, Deserialize_State *state) {
	bool result = false;

	switch (type) {
	case Collider_Null: {
		auto collider = scene_attach_collider(scene, node, Null, 0);
		Null temp; // we don't need to get value for null collider
		result = deserialize_fmt_text(state, "collider_data", reflect_info<Null>(), (char *)&temp);
	} break;

	case Collider_Circle: {
		auto collider = scene_attach_collider(scene, node, Circle, 0);
		result = deserialize_fmt_text(state, "collider_data", reflect_info<Circle>(), (char *)collider);
	} break;

	case Collider_Mm_Rect: {
		auto collider = scene_attach_collider(scene, node, Mm_Rect, 0);
		result = deserialize_fmt_text(state, "collider_data", reflect_info<Mm_Rect>(), (char *)collider);
	} break;

	case Collider_Capsule: {
		auto collider = scene_attach_collider(scene, node, Capsule, 0);
		result = deserialize_fmt_text(state, "collider_data", reflect_info<Capsule>(), (char *)collider);
	} break;

	case Collider_Polygon: {
		Array_View<Vec2> points;

		scoped_temporary_allocation();
		auto mark = push_temporary_allocator();
		result = deserialize_fmt_text(state, "collider_data", reflect_info(points), (char *)&points);
		pop_temporary_allocator(mark);

		if (!result) break;

		Collider_Attachment attachment;
		attachment.polygon_n = (u32)points.count;
		auto collider = scene_attach_collider(scene, node, Polygon, &attachment);
		collider->vertex_count = (u32)points.count;
		memcpy(collider->vertices, points.data, sizeof(Vec2) * points.count);
	} break;

		invalid_default_case();
	}

	return result;
}

bool deserialize_collider_group(Scene *scene, Entity *entity, Collider_Group *group, Deserialize_State *state) {
	u32 count;
	if (!deserialize_fmt_text(state, "collider_group_count", reflect_info(count), (char *)&count))
		return false;

	*group = scene_create_colliders(scene, entity, count);
	Collider_Type type;

	for (u32 index = 0; index < group->count; ++index) {
		if (!deserialize_fmt_text(state, "collider_type", reflect_info<Collider_Type>(), (char *)&type))
			return false;
		if (!deserialize_collider(scene, type, collider_node(group->handle, index), state))
			return false;
	}
	return true;
}

bool deserialize_entity(Scene *scene, Entity *entity, Deserialize_State *state) {
	bool result = deserialize_fmt_text(state, "type", reflect_info<Entity_Type>(), (char *)&entity->type);
	if (!result) return false;

	switch (entity->type) {
	case Entity_Player: {
		result = deserialize_fmt_text(state, "player", reflect_info<Player>(), (char *)entity);
		auto player = (Player *)entity;
		player->rigid_body = scene_create_rigid_body(scene, entity, 1);
		scene_attach_collider(scene, collider_node(player->rigid_body->colliders.handle, 0), Circle, 0);
	} break;

	case Entity_Static_Body: {
		if (!deserialize_fmt_text(state, "static_body", reflect_info<Static_Body>(), (char *)entity))
			return false;
		Collider_Group *group = &((Static_Body *)entity)->colliders;
		result = deserialize_collider_group(scene, entity, group, state);
	} break;

		invalid_default_case();
	}

	return result;
}

#endif
