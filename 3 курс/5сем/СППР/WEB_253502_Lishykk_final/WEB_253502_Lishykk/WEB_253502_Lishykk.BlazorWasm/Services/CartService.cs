using Blazored.LocalStorage;
using Microsoft.AspNetCore.Components.Authorization;
using System.Security.Claims;
using WEB_253502_Lishykk.BlazorWasm.Models;
using System.Text.Json;

namespace WEB_253502_Lishykk.BlazorWasm.Services
{
    public class CartService : IDisposable
    {
        private const string CartStorageKeyPrefix = "user_cart_";
        private const string AnonymousCartKey = "anonymous_cart";
        private readonly ILocalStorageService _localStorage;
        private readonly AuthenticationStateProvider _authStateProvider;

        private Dictionary<int, CartItem> _items = new();
        private string _currentUserId = null;
        

        public event Action OnChange;

        public CartService(
            ILocalStorageService localStorage,
            AuthenticationStateProvider authStateProvider)
        {
            _localStorage = localStorage;
            _authStateProvider = authStateProvider;
            _authStateProvider.AuthenticationStateChanged += OnUserChanged;
        }

        public async Task InitializeAsync()
        {
            var authState = await _authStateProvider.GetAuthenticationStateAsync();
            await UpdateUserCart(authState.User);
        }


        public IReadOnlyDictionary<int, CartItem> Items => _items;

        public async Task AddToCart(Car car, int quantity = 1)
        {
            if (_items.ContainsKey(car.Id))
            {
                _items[car.Id].Count += quantity;
            }
            else
            {
                _items[car.Id] = new CartItem { Item = car, Count = quantity };
            }

            await SaveCartAsync();
            NotifyStateChanged();
        }

        public async Task RemoveItem(int carId)
        {
            if (_items.Remove(carId))
            {
                await SaveCartAsync();
                NotifyStateChanged();
            }
        }

        public async Task ClearCart()
        {
            _items.Clear();
            await SaveCartAsync();
            NotifyStateChanged();
        }

        public async Task SaveBeforeLogout()
        {
            if (_currentUserId != null)
            {
                await SaveCartAsync();
            }
        }

        public decimal GetTotalPrice() =>
            _items.Sum(item => item.Value.Item.Price * item.Value.Count);

        public int GetTotalItems() =>
            _items.Sum(item => item.Value.Count);

        private async void OnUserChanged(Task<AuthenticationState> task)
        {
            var authState = await task;
            await UpdateUserCart(authState.User);
        }

        private async Task UpdateUserCart(ClaimsPrincipal user)
        {
            var previousUserId = _currentUserId;
            var isNowAuthenticated = user.Identity.IsAuthenticated;

            // Определяем новый ID пользователя
            //var newUserId = isNowAuthenticated
            //    ? user.FindFirst(ClaimTypes.NameIdentifier)?.Value
            //    : null;
            var newUserId = isNowAuthenticated
                ? user.Claims.FirstOrDefault(c => c.Type.Contains("nameidentifier") || c.Type == "sub")?.Value
                : null;

            // Если пользователь не изменился - ничего не делаем
            if (previousUserId == newUserId) return;

            // Сохраняем предыдущую корзину
            if (previousUserId != null)
            {
                await SaveCartAsync(previousUserId);
            }

            // Обновляем текущий ID пользователя
            _currentUserId = newUserId;

            // Если стал авторизованным - объединяем с анонимной корзиной
            if (isNowAuthenticated && previousUserId == null)
            {
                await MergeAnonymousCart();
            }

            // Загружаем новую корзину
            await LoadCartAsync();
            NotifyStateChanged();
        }

        private async Task MergeAnonymousCart()
        {
            try
            {
                var anonymousCart = await _localStorage.GetItemAsync<Dictionary<int, CartItem>>(AnonymousCartKey);
                if (anonymousCart == null || anonymousCart.Count == 0) return;

                // Объединяем корзины
                foreach (var item in anonymousCart)
                {
                    if (_items.ContainsKey(item.Key))
                    {
                        _items[item.Key].Count += item.Value.Count;
                    }
                    else
                    {
                        _items[item.Key] = item.Value;
                    }
                }

                // Удаляем анонимную корзину
                await _localStorage.RemoveItemAsync(AnonymousCartKey);
                await SaveCartAsync(); // Сохраняем объединенную корзину
            }
            catch (JsonException)
            {
                await _localStorage.RemoveItemAsync(AnonymousCartKey);
            }
        }

        private async Task LoadCartAsync()
        {
            try
            {
                var storageKey = GetStorageKey();
                var savedCart = await _localStorage.GetItemAsync<Dictionary<int, CartItem>>(storageKey);
                _items = savedCart ?? new Dictionary<int, CartItem>();
            }
            catch (JsonException)
            {
                _items = new Dictionary<int, CartItem>();
                await _localStorage.RemoveItemAsync(GetStorageKey());
            }
        }

        public async Task SaveCartAsync(string userId = null)
        {
            var storageKey = GetStorageKey(userId);
            Console.WriteLine($"Saving cart under key: {storageKey}");
            await _localStorage.SetItemAsync(storageKey, _items);
        }


        private string GetStorageKey(string userId = null)
        {
            var effectiveUserId = userId ?? _currentUserId;
            return effectiveUserId != null
                ? $"{CartStorageKeyPrefix}{effectiveUserId}"
                : AnonymousCartKey;
        }

        public void NotifyStateChanged() => OnChange?.Invoke();

        public void Dispose()
        {
            _authStateProvider.AuthenticationStateChanged -= OnUserChanged;
        }
    }
}