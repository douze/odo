#ifndef SCENE_H
#define SCENE_H

#include "mesh.hpp"
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
   * @note Used for scene root node.
   * @note Will be used for transform only node.
   */
  Node();

  /**
   * @brief Create a node with a mesh.
   * @param mesh to attach to the node
   */
  Node(std::shared_ptr<mesh::Mesh> mesh);

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

private:
  /** Mesh attached to the node. Can be null for transform only node. */
  std::shared_ptr<mesh::Mesh> mesh;

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
  Scene();
  
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
