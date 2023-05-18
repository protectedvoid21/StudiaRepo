import java.util.ArrayList;

public class BST<T> {
	private class Node{
		T value;
		Node left,right,parent;

		public Node(T v) {
			value=v;
		}

		public Node(T value, Node left, Node right, Node parent) {
			super();
			this.value = value;
			this.left = left;
			this.right = right;
			this.parent = parent;
		}
	}

	private Node root=null;

	public BST() {
	}
	
	private Node getNode(T toFind) {
		Comparable<T> findComp = (Comparable<T>)toFind;

		Node current = root;
		while(current != null) {
			int compResult = findComp.compareTo(current.value);

			if(compResult == 0) {
				return current;
			}

			if(compResult < 0) {
				current = current.left;
			}
			else {
				current = current.right;
			}
		}
		return null;
	}

	public T getElement(T toFind) {
		Node foundNode = getNode(toFind);
		
		if(foundNode == null) {
			return null;
		}
		return foundNode.value;
	}
	
	private Node getMin(Node branch) {
		Node current = branch;
		
		while(current.left != null) {
			current = current.left;
		}
		return current;
	} 

	public T successor(T elem) {
		var sucNode = successorNode(elem);
		if(sucNode == null) {
			return null;
		}
		return sucNode.value;
	}
	
	private Node successorNode(T elem) {
		Node elemNode = getNode(elem);
		if(elemNode == null) {
			return null;
		}

		if(elemNode.right != null) {
			return getMin(elemNode.right);
		}
		Node parentNode = elemNode;
		Node previousNode = elemNode;
		while(parentNode.left != previousNode && parentNode != root) {
			previousNode = parentNode;
			parentNode = previousNode.parent;
		}
		if(parentNode == root) {
			return null;
		}

		return parentNode;
	}
	
	private String getInorderForBranch(Node node) {
		if(node == null) {
			return "";
		}
		String text = "";

		text += getInorderForBranch(node.left);
		text += node.value + ", ";
		text += getInorderForBranch(node.right);
		
		return text;
	}

	private String getPreorderForBranch(Node node) {
		if(node == null) {
			return "";
		}
		String text = "";

		text += node.value + ", ";
		text += getPreorderForBranch(node.left);
		text += getPreorderForBranch(node.right);

		return text;
	}

	private String getPostorderForBranch(Node node) {
		if(node == null) {
			return "";
		}
		String text = "";

		text += getPostorderForBranch(node.left);
		text += getPostorderForBranch(node.right);
		text += node.value + ", ";

		return text;
	}
	
	private String removeLastChar(String text) {
		if(text.length() < 1) {
			return text;
		}
		return text.substring(0, text.length() - 2);
	}

	public String toStringInOrder() {
		String text = getInorderForBranch(root);
		return removeLastChar(text);
	}

	public String toStringPreOrder() {
		String text = getPreorderForBranch(root);
		return removeLastChar(text);
	}

	public String toStringPostOrder() {
		String text = getPostorderForBranch(root);
		return removeLastChar(text);
	}


	public boolean add(T elem) {
		if(root == null) {
			root = new Node(elem);
			return true;
		}
		
		Comparable<T> elemComp = (Comparable<T>)elem;

		Node nextNode = root;
		
		while(true) {
			int compResult = elemComp.compareTo(nextNode.value);
			
			if(compResult == 0) {
				return false;
			}
			if(compResult < 0) {
				if(nextNode.left == null) {
					nextNode.left = new Node(elem, null, null, nextNode);
					return true;
				}
				nextNode = nextNode.left;
			}
			else {
				if(nextNode.right == null) {
					nextNode.right = new Node(elem, null, null, nextNode);
					return true;
				}
				nextNode = nextNode.right;
			}
		}
	}

	public T remove(T value) {
		Node elemNode = getNode(value);
		if(elemNode == null) {
			return null;
		}
		
		T elemValue = elemNode.value;
		
		if(elemNode.left == null && elemNode.right == null) {
			if(elemNode == root) {
				root = null;
				return elemValue;
			}
			removeFromParent(elemNode);
			return elemValue;
		}
		if(elemNode.left != null && elemNode.right != null) {
			Node succ = successorNode(value);
			remove(succ.value);
			elemNode.value = succ.value;
			return elemValue;
		}
		
		Node child = elemNode.left == null ? elemNode.right : elemNode.left;
		if(elemNode == root) {
			root = child;
			root.parent = null;
			return elemValue;
		}
		
		if(elemNode.parent.left == elemNode) {
			elemNode.parent.left = child;
		}
		else {
			elemNode.parent.right = child;
		}
		child.parent = elemNode.parent;
		return elemValue;
	}
	
	public int leafCount() {
		if(root == null) {
			return 0;
		}
		
		int leafs = 0;

		var nodes = new ArrayList<Node>();
		
		nodes.add(root);
		while(!nodes.isEmpty()) {
			var lowerNodes = new ArrayList<Node>();
			for(var node : nodes) {
				if(!isLeaf(node)) {
					if(node.left != null) {
						lowerNodes.add(node.left);
					}
					if(node.right != null) {
						lowerNodes.add(node.right);
					}
				}
				else {
					leafs++;
				}
			}
			nodes = lowerNodes;
		}
		return leafs;
	}
	
	private boolean isLeaf(Node node) {
		return node.left == null && node.right == null;
	}
	
	private void removeFromParent(Node node) {
		Node parent = node.parent;
		if(parent == null) {
			return;
		}
		if(node == parent.right) {
			parent.right = null;
		}
		else {
			parent.left = null;
		}
	}

	public void clear() {
		root = null;
	}

	public int size() {
		return branchSize(root);
	}

	private int branchSize(Node branch) {
		if(branch == null) {
			return 0;
		}
		int size = 1;
	
		size += branchSize(branch.left);
		size += branchSize(branch.right);
		
		return size;
	}
}
