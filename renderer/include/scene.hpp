#ifndef SCENE_H
#define SCENE_H

#include "material.hpp"
#include "mesh.hpp"
#include "transformation.hpp"
#include <memory>
#include <vector>

namespace renderer {
namespace scene {

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
  explicit Node(const std::shared_ptr<mesh::Mesh>& mesh,
                mesh::Transformation transformation,
                const std::shared_ptr<material::Material>& material) noexcept;

  /**
   * @brief Add a node child to the current node.
   * @param child to add
   */
  void addChild(Node& child);

  /**
   * @brief Return the node's mesh by const reference.
   */
  const std::shared_ptr<mesh::Mesh>& getMesh() const { return mesh; }

  /**
   * @brief Return the node's children by const reference.
   */
  const std::vector<std::reference_wrapper<Node>>& getChildren() const {
    return children;
  }

  /**
   * @brief Return the node's transformation.
   */
  mesh::Transformation getTransformation() const {
    return transformation;
  }
  
  glm::mat4 getTransMat() {
   return transformation.getMatrix(); 
  }

  /**
   * @brief Return the node's material.
   */
  const std::shared_ptr<material::Material>& getMaterial() const { return material; }

private:
  /** Mesh attached to the node. Can be null for transform only node. */
  std::shared_ptr<mesh::Mesh> mesh;

  /** Transformation attached to the node */
  mesh::Transformation transformation;

  std::shared_ptr<material::Material> material;

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
   * @brief Return the scene's root by const reference.
   */
  const std::unique_ptr<Node>& getRoot() { return root; }

private:
  /** Scene root */
  std::unique_ptr<Node> root;
};

} // namespace scene
} // namespace renderer

#endif // SCENE_H
