/**
 * @param {number} init
 * @return {{increment: () => number, decrement: () => number, reset: () => number}}
 */
var createCounter = function(init) {
  let cur = init;          // store current value in closure

  return {
    increment: function() {
      cur = cur + 1;       // or ++cur
      return cur;
    },
    decrement: function() {
      cur = cur - 1;       // or --cur
      return cur;
    },
    reset: function() {
      cur = init;          // reset to original init
      return cur;
    }
  };
};
