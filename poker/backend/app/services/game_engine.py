from typing import Tuple

from ..models.game_state import GameState
from ..models.game_action import GameAction
from ..core.enums import PlayerState, Street, Action
from ..models.player import Player
from ..core.config import MIN_PLAYER_COUNT, MAX_PLAYER_COUNT

# Core game flow logic
def start_game(state: GameState) -> None:
    if state.num_players < MIN_PLAYER_COUNT or state.num_players > MAX_PLAYER_COUNT:
        pass
    state.toggle_pause()
    start_round(state)

def start_round(state: GameState) -> None:
    street: Street = state.street
    if street == Street.PRE_FLOP:
        round_state_reset(state)
        deal_hands(state, 2)
        post_blinds(state)
    elif street == Street.FLOP:
        deal_street(state, 3)
    elif street == Street.TURN:
        deal_street(state, 1)
    elif street == Street.RIVER:
        deal_street(state, 1)
    elif street == Street.SHOWDOWN:
        end_round(state)

        pass
        #TODO rotate player positions
    else:
        pass

# Deck funcs
def deal_hands(state: GameState, num_cards: int) -> None:
    for _ in range(num_cards):
        for player in state.players:
            if player.state == PlayerState.ACTIVE:
                player.cards.append(state.deck.deal_card())

def deal_street(state: GameState, num_cards: int) -> None:
    for _ in range(num_cards):
        state.deck.deal_card()  # burn
        state.board.append(state.deck.deal_card())

# Betting funcs
def post_blinds(state: GameState) -> None:
    sb: int = 1
    bb: int = 2
    sb_player = state.players[0]
    bb_player = state.players[1]

    make_bet(sb_player, sb)
    set_bet_to_match(state, sb)
    make_bet(bb_player, bb)
    set_bet_to_match(state, bb)

    sb_player.has_acted = False
    bb_player.has_acted = False

def make_action(state: GameState, player_index: int, game_action: GameAction) -> None:
    player = state.players[player_index]
    action = game_action.action
    bet = game_action.bet
    #TODO add validation to bet and action

    if action == Action.FOLD:
        player.state = PlayerState.FOLDED
        state.active_player_count -= 1

        state.pot += player.current_bet
        player.current_bet = 0

        player.cards.clear()
    elif action == Action.CHECK:
        player.has_acted = True
    elif action == Action.CALL:
        make_bet(player, bet)
    elif action == Action.RAISE:
        make_bet(player, bet - player.current_bet)
        set_bet_to_match(state, bet)
    elif action == Action.ALL_IN:
        player.state = PlayerState.ALL_IN
        state.active_player_count -= 1
        
        make_bet(player, bet - player.current_bet)
        set_bet_to_match(state, bet)

    round_over = (state.active_player_count <= 1)
    betting_over = progress_round(state)
    print(f"betting_over: {betting_over}, round_over: {round_over}")
    if round_over:
        end_round(state)
    elif betting_over:
        progress_street(state)

def make_bet(player: Player, bet: int) -> None:
    player.stack -= bet
    player.current_bet += bet

    player.has_acted = True

def set_bet_to_match(state: GameState, bet: int):
    if bet > state.current_bet_to_match:
        state.previous_bet_to_match = state.current_bet_to_match
        state.current_bet_to_match = bet

# Util funcs
def progress_round(state: GameState) -> Tuple[bool, bool]:
    # if everyone folded except 1
    # if everyone is all in
    # if everyone is away
    curr_idx = state.current_player_index
    while True:
        state.increment_player_index()
        print(f"idx: {state.current_player_index}")

        if state.current_player_index == curr_idx:
            return True
        
        player = state.players[state.current_player_index]
        active: bool = (player.state == PlayerState.ACTIVE)
        matched_bet: bool = (player.current_bet >= state.current_bet_to_match)
        acted: bool = player.has_acted

        #print(f"for player {player.name}")
        #print(f"active: {active}, matched_bet: {matched_bet}, acted: {acted}")

        if active and not (matched_bet and acted):
            return False
        
def progress_street(state: GameState) -> None:
    state.next_street()
    if state.street == Street.PRE_FLOP:
        state.current_player_index = 2
    else:
        state.current_player_index = 0

    street_state_reset(state)
    start_round(state)

def street_state_reset(state: GameState) -> None:
    state.previous_bet_to_match = 0
    state.current_bet_to_match = 0
    for player in state.players:
        state.pot += player.current_bet

        player.current_bet = 0
        player.has_acted = False

def end_round(state: GameState) -> None:
    distribute_winnings(state)
    round_state_reset(state)
    rotate_positions(state)

def round_state_reset(state: GameState) -> None:
    state.board.clear()
    state.reset_deck()
    state.previous_bet_to_match = 0
    state.current_bet_to_match = 0
    state.street = Street.PRE_FLOP

    active_players: int = 0
    for player in state.players:
        if player.state is not PlayerState.AWAY:
            player.state = PlayerState.ACTIVE
            active_players += 1
        player.cards.clear()
        player.current_bet = 0
        player.has_acted = False
    state.active_player_count = active_players

def rotate_positions(state: GameState):
    pass

def distribute_winnings(state: GameState) -> None:
    #print(f"active: {state.active_player_count}")
    # if one player -> wins
    if state.active_player_count == 1:
        for player in state.players:
            if player.state == PlayerState.ACTIVE:
                player.stack += player.current_bet
                player.stack += state.pot

                state.pot = 0
                break
    # if more calculate winner
    # handle split pots
    # handle side pots
    # implement splitting odd pots logic
    pass