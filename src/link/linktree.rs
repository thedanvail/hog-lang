use std::fs::File;

pub struct Node {
    pub file: File,
    pub adjacent_nodes: Vec<Node>,
}

pub struct Graph {
    pub root: Node,
}
