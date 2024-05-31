import pygame

from state import State


class RunGame:
    _current_state: State = None
    
    def __init__(self, initial_state: State):
        self._current_state = initial_state
        
        
    def run(self):
        while self._current_state is not None:
            self._current_state = self._current_state.update()