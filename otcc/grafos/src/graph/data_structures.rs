use std::collections::HashMap;
use std::hash::Hash;
use std::hash::Hasher;

use super::errors::GraphError;

pub type VertexId = usize;

#[derive(Copy, Debug)]
struct Vertex<T> {
    id: VertexId,
    data: Option<T>,
}

impl<T> PartialEq for Vertex<T> {
    fn eq(&self, other: &Self) -> bool {
        self.id == other.id
    }
}

impl<T> Eq for Vertex<T> {}

impl<T> Hash for Vertex<T> {
    fn hash<H: Hasher>(&self, state: &mut H) {
        self.id.hash(state);
    }
}

impl<T: Clone> Clone for Vertex<T> {
    fn clone(&self) -> Self {
        Self {
            id: self.id,
            data: self.data.clone(),
        }
    }
}

#[derive(PartialEq, Eq, Debug)]
pub struct Graph<T> {
    vertices: HashMap<VertexId, Vec<Vertex<T>>>,
}

#[allow(dead_code)]
impl<T> Vertex<T> {
    fn new(id: VertexId, data: Option<T>) -> Self {
        Vertex { id, data }
    }
}

#[allow(dead_code)]
impl<T> Graph<T>
where
    T: Clone,
{
    fn new() -> Self {
        Self {
            vertices: HashMap::new(),
        }
    }

    fn from_edges(edges: Vec<(VertexId, VertexId)>) -> Self {
        let mut graph = Self::new();

        edges.iter().for_each(|(start, end)| {
            let start_vertex = Vertex::new(*start, None::<T>);
            let end_vertex = Vertex::new(*end, None::<T>);

            let _ = graph.add_vertex(start_vertex.clone());
            let _ = graph.add_vertex(end_vertex.clone());

            graph.add_edge(start_vertex, end_vertex);
        });

        graph
    }

    fn add_vertex(&mut self, vertex: Vertex<T>) -> Result<(), GraphError> {
        if let Some(_key) = self.vertices.get(&vertex.id) {
            return Err(GraphError::VertexAlreadyExists(vertex.id));
        }

        self.vertices.insert(vertex.id, Vec::new());

        Ok(())
    }

    fn add_edge(&mut self, start: Vertex<T>, end: Vertex<T>) -> ()
    where
        T: Clone,
    {
        let start_neighbors = self.vertices.entry(start.id).or_insert_with(Vec::new);
        if !start_neighbors.contains(&end) {
            start_neighbors.push(end.clone());
        }

        let end_neighbors = self.vertices.entry(end.id).or_insert_with(Vec::new);
        if !end_neighbors.contains(&start) {
            end_neighbors.push(start);
        }
    }

    fn vertex_degree(&self, id: VertexId) -> Result<usize, GraphError> {
        let edges = self.vertices.get(&id);

        match edges {
            Some(vec) => Ok(vec.len()),
            None => Err(GraphError::VertexNotFound(id)),
        }
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn create_graph() {
        let graph = Graph::<u32>::new();

        assert_eq!(
            graph,
            Graph {
                vertices: HashMap::new(),
            }
        );
    }

    #[test]
    fn add_vertex() {
        let mut graph = Graph::<u32>::new();
        let vertex = Vertex::new(0, Some(10));

        let _ = graph.add_vertex(vertex);

        assert_eq!(graph.vertices.get(&0), Some(&Vec::<Vertex<u32>>::new()));
    }

    #[test]
    fn add_edge() {
        let mut graph = Graph::new();
        let v1 = Vertex {
            id: 1,
            data: Some(5),
        };
        let v2 = Vertex { id: 2, data: None };

        graph.add_edge(v1, v2);

        assert!(graph.vertices.contains_key(&v1.id));
        assert!(graph.vertices.contains_key(&v2.id));
        assert_eq!(graph.vertices[&v1.id], vec![v2]);
        assert_eq!(graph.vertices[&v2.id], vec![v1]);
    }
}
