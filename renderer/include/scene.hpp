#ifndef SCENE_H
#define SCENE_H

#include "camera.hpp"
#include "material.hpp"
#include "mesh.hpp"
#include "transformation.hpp"
#include <memory>
#include <vector>

namespace odo::scene {

/**
 * @brief Scene node. A node contains a mesh.
 * @note Will contains a transform in a near future.
 */
class Node {
public:
  /**
   * @brief Create a node without mesh.
   * @param transformation for the root node
   * @note Used for scene root node.
   */
  explicit Node(mesh::Transformation transformation) noexcept;

  /**
   * @brief Create a node with a mesh.
   * @param mesh to attach to the node
   */
  explicit Node(std::unique_ptr<mesh::Mesh> mesh, std::unique_ptr<material::Material> material,
                mesh::Transformation transformation) noexcept;

  /**
   * @brief Add a node child to the current node.
   * @param child to add
   */
  void add_child(Node& child);

  /**
   * @return the node's mesh.
   */
  mesh::Mesh& get_mesh() const { return *mesh.get(); }

  /**
   * @return the node's material.
   */
  const material::Material& get_material() const { return *material.get(); }

  /**
   * @return the node's transformation.
   */
  mesh::Transformation get_transformation() const { return transformation; }

  /**
   * @return the node's children.
   */
  const std::vector<std::reference_wrapper<Node>>& get_children() const { return children; }

  /**
   * @return true if the node is renderable.
   */
  bool is_renderable() const { return mesh != nullptr && material != nullptr; }

private:
  /** Mesh attached to the node. Can be null for transform only node. */
  std::unique_ptr<mesh::Mesh> mesh;

  /** Material attached to the node. Can be null for transform only node. */
  std::unique_ptr<material::Material> material;

  /** Transformation attached to the node */
  mesh::Transformation transformation;

  /** Children of the node. Used for scene graph.  */
  std::vector<std::reference_wrapper<Node>> children;
};

/**
 * @brief Scene graph, mainly used to store mesh to render.
 */
class Scene {
public:
  /**
   * @brief Create an empty scene.
   */
  explicit Scene() noexcept;

  /**
   * @return the scene's root.
   */
  Node& get_root() { return root; }

  /**
   * @brief Attach the main camera to the scene.
   * @note Main camera is used for standard rendering.
   * @param camera to attach
   */
  void attach_main_camera(std::shared_ptr<Camera> camera) { this->camera = camera; }

  /**
   * @return the main camera of the scene.
   */
  Camera& get_main_camera() const { return *camera.get(); }

private:
  /** Scene root */
  Node root;

  /** Main camera used to render the scene */
  std::shared_ptr<Camera> camera;
};

} // namespace odo::scene

#endif // SCENE_H
