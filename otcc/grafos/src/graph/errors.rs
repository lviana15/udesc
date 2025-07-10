use std::fmt::Display;

use super::data_structures::VertexId;

#[allow(dead_code)]
pub enum GraphError {
    VertexNotFound(VertexId),
    VertexAlreadyExists(VertexId),
}

impl Display for GraphError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            GraphError::VertexNotFound(id) => write!(f, "Vertex {} not found", id),
            GraphError::VertexAlreadyExists(id) => {
                write!(f, "Vertex {} already exists", id)
            }
        }
    }
}
