function menuClicked(e) {
  $('html, body').animate({scrollTop: $($.attr(this, 'href')).offset().top}, 600, 'swing');

  window.history.pushState("", "", $.attr(this, 'href'));
  return false;
}

$(document).ready(function() {
  $("a").click(menuClicked);
});
