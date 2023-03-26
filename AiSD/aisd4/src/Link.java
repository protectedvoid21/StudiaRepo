public class Link implements Comparable<Link>{
    public String ref;
    public int weight;
    public Link(String ref) {
        this.ref=ref;
        weight=1;
    }
    public Link(String ref, int weight) {
        this.ref=ref;
        this.weight=weight;
    }
    @Override
    public boolean equals(Object obj) {
        if(obj.getClass() != getClass()) {
            return false;
        }
        if(this == obj) {
            return true;
        }
        Link other = (Link)obj;
        
        return ref.equals(other.ref);
    }
    @Override
    public String toString() {
        return ref+"("+weight+")";
    }
    @Override
    public int compareTo(Link another) {
        return weight - another.weight;
    }
}
