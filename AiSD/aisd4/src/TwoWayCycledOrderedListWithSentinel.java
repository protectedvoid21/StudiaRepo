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
    int size;

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
        //TODO DODAC WALIDACJE
        
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
        Element current = sentinel;
        
        while(index > 0) {
            current = current.next;
            if(current == null) {
                throw new NoSuchElementException();
            }
            index--;
        }
        
        return current;
    }

    private Element getElement(E obj) {
        Element current = sentinel;
        
        while(current.next != null) {
            current = current.next;
            if(current.object.equals(obj)) {
                return current;
            }
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
        Element current = sentinel;
        int index = 0;
        
        while(current.next != null) {
            current = current.next;
            
            if(current.object.equals(e)) {
                return index;
            }
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
        Element current = sentinel;
        
        while(current.next != sentinel) {
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
        if(isEmpty()) {
            sentinel.next = other.sentinel.next;
            sentinel.prev = other.sentinel.prev;
            other.clear();
            return;
        }
        
        Element current = sentinel.next;
        Element otherCurrent = other.sentinel.next;
        
        
        // 1 3 5 7 9    dodajemy 4
        // 1 3 4 5 7 9 
        while(otherCurrent != other.sentinel) {
            if(current == sentinel) {
                current.addAfter(new Element(otherCurrent.object));
                otherCurrent = otherCurrent.next;
                current = current.next;
                continue;
            }
            if(current.object.compareTo(otherCurrent.object) > 0) {
                current.prev.addAfter(new Element(otherCurrent.object));
                otherCurrent = otherCurrent.next;
                continue;
            }
            current = current.next;
        }
        
        current.next = sentinel;
        sentinel.prev = current;
        
        other.clear();
    }

    //@SuppressWarnings({ "unchecked", "rawtypes" })
    public void removeAll(E e) {
        Element current = sentinel;
        
        while(current.next != sentinel) {
            current = current.next;
            
            if(current.object.equals(e)) {
                current.remove();
            }
        }
    }

}
