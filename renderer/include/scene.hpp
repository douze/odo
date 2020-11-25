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
  explicit Node(std::unique_ptr<mesh::Mesh> mesh,
                mesh::Transformation transformation,
                std::unique_ptr<material::Material> material) noexcept;

  /**
   * @brief Add a node child to the current node.
   * @param child to add
   */
  void addChild(Node& child);

  /**
   * @brief Return the node's mesh by const reference.
   */
  //   const std::shared_ptr<mesh::Mesh>& getMesh() const { return mesh; }
  mesh::Mesh& getMesh() const { return *mesh.get(); }

  /**
   * @brief Return the node's children by const reference.
   */
  const std::vector<std::reference_wrapper<Node>>& getChildren() const {
    return children;
  }

  /**
   * @brief Return the node's transformation.
   */
  mesh::Transformation getTransformation() const { return transformation; }

  /**
   * @brief Return the node's material.
   */
  const material::Material& getMaterial() const { return *material.get(); }

  bool isRenderable() const { return mesh != nullptr && material != nullptr; }

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
   * @brief Return the scene's root by reference.
   */
  Node& getRoot() { return root; }

  void setCamera(std::shared_ptr<Camera> camera) { this->camera = camera; }
  Camera& getCamera() const { return *camera.get(); }

private:
  /** Scene root */
  Node root;

  /** Main camera used to render the scene */
  std::shared_ptr<Camera> camera;
};

} // namespace odo::scene

#endif // SCENE_H
