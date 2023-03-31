import java.nio.file.Path;
import java.util.Iterator;
import java.util.ListIterator;
import java.util.NoSuchElementException;

public class TwoWayCycledOrderedListWithSentinel<E extends Comparable<E>> implements IList<E>{

    private class Element{
        public Element(E e) {
            object = e;
        }
        public Element(E e, Element next, Element prev) {
            object = e;
            this.next = next;
            this.prev = prev;
        }
        // add element e after this
        public void addAfter(Element elem) {
            elem.next = next;
            elem.prev = this;
            next.prev = elem;
            next = elem;
        }
        // assert it is NOT a sentinel
        public void remove() {
            if(this == sentinel) {
                return;
            }
            
            prev.next = next;
            next.prev = prev;
        }
        E object;
        Element next=null;
        Element prev=null;
    }


    Element sentinel;

    private class InnerIterator implements Iterator<E>{
        private Element current;
        
        public InnerIterator() {
            current = sentinel;
        }
        @Override
        public boolean hasNext() {
            return current.next != sentinel;
        }

        @Override
        public E next() {
            current = current.next;
            return current.object;
        }
    }

    private class InnerListIterator implements ListIterator<E>{
        private Element current;
        
        public InnerListIterator() {
            current = sentinel;
        }
        @Override
        public boolean hasNext() {
            return current.next != sentinel;
        }

        @Override
        public E next() {
            current = current.next;
            return current.object;
        }
        @Override
        public void add(E arg0) {
            throw new UnsupportedOperationException();
        }
        @Override
        public boolean hasPrevious() {
            return current != sentinel;
        }
        @Override
        public int nextIndex() {
            throw new UnsupportedOperationException();
        }
        @Override
        public E previous() {
            E value = current.object;
            current = current.prev;
            return value;
        }
        @Override
        public int previousIndex() {
            throw new UnsupportedOperationException();
        }
        @Override
        public void remove() {
            throw new UnsupportedOperationException();
        }
        @Override
        public void set(E arg0) {
            throw new UnsupportedOperationException();
        }
    }
    public TwoWayCycledOrderedListWithSentinel() {
        sentinel = new Element(null);
        sentinel.next = sentinel;
        sentinel.prev = sentinel;
    }

    //@SuppressWarnings("unchecked")
    @Override
    public boolean add(E e) {
        Link link = (Link)e;
        if(!Document.correctLink(link.ref)) {
            return false;
        }
        
        Element current = sentinel;
        
        while(current.next != sentinel) {
            current = current.next;
            if(current.object.compareTo(e) > 0) {
                current.prev.addAfter(new Element(e));
                return true;
            }
        }
        current.addAfter(new Element(e));
        sentinel.prev = current.next;
        return true;
    }

    private Element getElement(int index) {
        if(index < 0) {
            throw new NoSuchElementException();
        }
        
        if(isEmpty()) {
            throw new NoSuchElementException();
        }
        
        Element current = sentinel.next;
        
        while(index > 0) {
            if(current.next == sentinel) {
                throw new NoSuchElementException();
            }
            current = current.next;
            index--;
        }
        
        return current;
    }

    private Element getElement(E obj) {
        Element current = sentinel.next;
        
        while(current != sentinel) {
            if(current.object.equals(obj)) {
                return current;
            }
            current = current.next;
        }
        return null;
    }

    @Override
    public void add(int index, E e) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void clear() {
        sentinel.next = sentinel;
        sentinel.prev = sentinel;
    }

    @Override
    public boolean contains(E e) {
        return getElement(e) != null;
    }

    @Override
    public E get(int index) {
        return getElement(index).object;
    }

    @Override
    public E set(int index, E e) {
        throw new UnsupportedOperationException();
    }

    @Override
    public int indexOf(E e) {
        Element current = sentinel.next;
        int index = 0;
        
        while(current != sentinel) {
            if(current.object.equals(e)) {
                return index;
            }
            current = current.next;
            index++;
        }
        
        return -1;
    }

    @Override
    public boolean isEmpty() {
        return sentinel.next == sentinel;
    }

    @Override
    public Iterator<E> iterator() {
        return new InnerIterator();
    }

    @Override
    public ListIterator<E> listIterator() {
        return new InnerListIterator();
    }

    @Override
    public E remove(int index) {
        Element element = getElement(index);
        element.remove();
        
        return element.object;
    }

    @Override
    public boolean remove(E e) {
        Element element = getElement(e);
        if(element == null) {
            return false;
        }
        element.remove();
        
        return true;
    }

    @Override
    public int size() {
        int size = 0;
        Element current = sentinel.next;
        
        while(current != sentinel) {
            current = current.next;
            size++;
        }
        return size;
    }

    //@SuppressWarnings("unchecked")
    public void add(TwoWayCycledOrderedListWithSentinel<E> other) {
        if(other == this || other.isEmpty()) {
            return;
        }
        
        Element current = sentinel.next;
        Element otherCurrent = other.sentinel.next;
        
        while(current != sentinel) {
            if(otherCurrent.object.compareTo(current.object) < 0) {
                Element nextOther = otherCurrent.next;
                otherCurrent.next = current;
                otherCurrent.prev = current.prev;
                current.prev.next = otherCurrent;
                current.prev = otherCurrent;
                
                otherCurrent = nextOther;
                
                if(otherCurrent == other.sentinel) {
                    break;
                }
            }
            else {
                current = current.next;
            }
            
        }
        
        if(otherCurrent != other.sentinel) {
            current.prev.next = otherCurrent;
            otherCurrent.prev = current.prev;
            
            sentinel.prev = other.sentinel.prev;
            sentinel.prev.next = sentinel;
        }
        
        other.clear();
    }

    //@SuppressWarnings({ "unchecked", "rawtypes" })
    public void removeAll(E e) {
        Element current = sentinel.next;
        
        while(current != sentinel) {
            if(current.object.equals(e)) {
                current.remove();
            }
            current = current.next;
        }
    }

}
