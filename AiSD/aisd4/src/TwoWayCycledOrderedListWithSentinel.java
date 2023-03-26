import java.nio.file.Path;
import java.util.Iterator;
import java.util.ListIterator;
import java.util.NoSuchElementException;

public class TwoWayCycledOrderedListWithSentinel<E> implements IList<E>{

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
            current = current.prev;
            return current.object;
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
    }

    //@SuppressWarnings("unchecked")
    @Override
    public boolean add(E e) {
        //TODO
        return false;
    }

    private Element getElement(int index) {
        if(index < 0 || index > size - 1) {
            throw new NoSuchElementException();
        }
        Element current = sentinel;
        
        while(index > 0) {
            current = current.next;
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
        sentinel.next = null;
        sentinel.prev = null;
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
        return sentinel.next == null;
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
        
        while(current.next != null) {
            size++;
        }
        return size;
    }

    //@SuppressWarnings("unchecked")
    public void add(TwoWayCycledOrderedListWithSentinel<E> other) {
        if(other == this || other.isEmpty()) {
            return;
        }
        
        Element tail = sentinel;
        while(tail.next != null) {
            tail = tail.next;
        }
        
        tail.next = other.sentinel.next;
        tail.next.prev = tail;
        
        while(tail.next != null) {
            tail = tail.next;
        }
        tail.next = sentinel;
        sentinel.prev = tail;
        
        other.clear();
    }

    //@SuppressWarnings({ "unchecked", "rawtypes" })
    public void removeAll(E e) {
        Element current = sentinel;
        
        while(current.next != null) {
            current = current.next;
            
            if(current.object.equals(e)) {
                current.remove();
            }
        }
    }

}
